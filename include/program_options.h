#pragma once

#include <string>

const char* const LOG_DIR = "logs";
const char* const CONF_FILE = "project.conf";
const char* const PID_FILE = "project.pid";

struct ProgramOptions
{
	static ProgramOptions& inst() {static ProgramOptions param; return param;}

	void load(int argc, char* argv[]);
	void load(const std::string& filename);

	// read from console options
	std::string log_dir;
	std::string conf_file;
	std::string pid_file;

	// read from config_file
	std::string author;
};

typedef ProgramOptions POptions;
