#pragma once

#include <list>
#include <boost/shared_ptr.hpp>
#include <boost/thread/mutex.hpp>
#include "program_options.h"
#include "thread.h"
#include "pid.h"

/*
 * Инициирует останов Mediator, вызывая Mediator::exit()
 */
void exit_sig_handler(int sig);

/*
 * Устанавливаем обработчик exit_sig_handler для сигналов
 * SIGINT(1) - сочетание клавиш Ctrl+C
 * SIGTERM(15) - «вежливое» завершение программы
 * SIGTSTP(20) - сочетание клавиш Ctrl+Z 
 */
void set_exit_sig_handlers();

class Mediator: public Thread
{
public:
	Mediator();
	virtual ~Mediator();

	void wait_exit();
	static void exit();

private:
	virtual void run();

	void load_app_configuration();
	void create_pid();

private:
	static bool exit_;
	static boost::mutex exit_mtx_;
	static boost::condition_variable exit_cv_;

	Pid pid_;
};


