/*
 * pid.cpp
 *
 *  Created on: 23.11.2012
 *      Author: rsergeev
 */

#include "pid.h"

#include <stdexcept>
#include <fstream>

#ifdef _WIN32
#include <process.h>
#else
#include <sys/types.h>
#include <unistd.h>
#endif

using namespace std;

void Pid::create(const std::string& pid_file)
{
	filename_ = pid_file;

	ofstream pf;
	pf.exceptions ( ofstream::failbit | ofstream::badbit );

	try
	{
		pf.open(filename_.c_str());

	#ifdef _WIN32
		size_t pid = _getpid();
	#else
		size_t pid = getpid();
	#endif

		pf << pid;
		pf.close();
	}
	catch(...)
	{
		if(pf.is_open())
			pf.close();
		throw std::runtime_error("Can't create pid file. Perhaps no write permission or the specified path does not exist");
	}
}

Pid::~Pid()
{
	if(!filename_.empty())
		remove(filename_.c_str());
}


