#include "program_options.h"
#include <sys/stat.h>
#include <iostream>
#include <fstream>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/program_options.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>

#include "version.h"

using namespace boost::program_options;
using namespace boost::filesystem;

void ProgramOptions::load(int argc, char* argv[])
{
	options_description desc("Allowed options");
	desc.add_options()
	    ("help,h", "produce help message")
	    ("config,c", value<std::string>(&conf_file)->default_value(std::string(CONF_FILE)), "set configuration file")
	    ("logdir,l", value<std::string>(&log_dir)->default_value(std::string(LOG_DIR)), "set log directory")
		("pidfile,p", value<std::string>(&pid_file)->default_value(std::string(PID_FILE)), "set pid file")
	;

	variables_map vm;
	store(parse_command_line(argc, argv, desc), vm);
	notify(vm);

	if (vm.count("help")) {
	    std::cout << desc << "\n";
	    exit(0);
	}
	std::cout << "Will be used the next options:" << std::endl
				<< "CONF_FILE = " << conf_file << std::endl
				<< "LOG_DIR = " << log_dir << std::endl
				<< "PID_DIR = " << pid_file << std::endl
			;
}

void ProgramOptions::load(const std::string& filename)
{
	std::ifstream file(conf_file.c_str());
	if(!file.is_open())
		throw std::runtime_error("Can't open configuration file");
	
	options_description desc;
	desc.add_options()
		("author", value<std::string>(&author), "Name of Creator")
    	;

	variables_map vm;
	store( parse_config_file<char>(file, desc), vm);
	notify(vm);
	file.close();
}