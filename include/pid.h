#pragma once

#include <string>

class Pid
{
public:
	// throw exception if something wrong
	void create(const std::string&);
	~Pid();
private:
	std::string filename_;
};
