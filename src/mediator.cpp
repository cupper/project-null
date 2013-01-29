#include "mediator.h"

#include <signal.h>
#include <fstream>
#include <boost/bind.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include "logger.h"


bool Mediator::exit_ = false;
boost::mutex Mediator::exit_mtx_;
boost::condition_variable Mediator::exit_cv_;

void exit_sig_handler(int sig)
{
	Mediator::exit();
}

void set_exit_sig_handlers()
{
	struct sigaction act;
	memset(&act, 0, sizeof(act));
	act.sa_handler = exit_sig_handler;
	sigset_t   set;
	sigemptyset(&set);
	sigaddset(&set, SIGINT);
	sigaddset(&set, SIGTERM);
	sigaddset(&set, SIGTSTP);
	act.sa_mask = set;
	sigaction(SIGINT, &act, 0);
	sigaction(SIGTERM, &act, 0);
	sigaction(SIGTSTP, &act, 0);
}

Mediator::Mediator()
{

}

Mediator::~Mediator()
{

}

void Mediator::wait_exit()
{
	LOG("wait exit");

	boost::unique_lock<boost::mutex> lock(exit_mtx_);
	while (!exit_)
		exit_cv_.wait(lock);

	LOG("stop application");
	stop();
}

void Mediator::exit()
{
	LOG("set exit");
	{
		boost::lock_guard<boost::mutex> lock(exit_mtx_);
		exit_ = true;
	}
	exit_cv_.notify_one();
}

void Mediator::run()
{
	try {
		create_pid();
		load_app_configuration();

		try {
			while (1) {
				boost::this_thread::sleep(
						boost::posix_time::seconds(1));
				// do something
			}
		} catch (boost::thread_interrupted const&) {
			LOG("leave");
		}
	} catch (std::exception& ex) {
		LOG_ERR("error occurred. %s", ex.what());
		exit();
	}
}

void Mediator::load_app_configuration()
{
	POptions& param = POptions::inst();
	LOG("load app configuration: %s", param.conf_file.c_str());

	param.load(param.conf_file);

	LOG("log_directory = %s", param.log_dir.c_str());
	LOG("config_file = %s", param.conf_file.c_str());
	LOG("pidfile = %s", param.pid_file.c_str());

	LOG("author = %s", param.author.c_str());
}

void Mediator::create_pid()
{
	LOG("create pid file: %s", POptions::inst().pid_file.c_str());
	pid_.create(POptions::inst().pid_file);
}
