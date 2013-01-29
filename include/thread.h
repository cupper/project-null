#pragma once

#include <boost/thread.hpp>
#include <boost/bind.hpp>

class Thread
{
public:
	void start() {th_ = boost::thread(boost::bind(&Thread::run, this));}
	void stop() {th_.interrupt(); th_.join();}

	virtual ~Thread(){}
private:
	virtual void run() = 0;
private:
	boost::thread th_;
};
