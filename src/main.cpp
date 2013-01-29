#if !defined(WINDOWS_PLATFORM)
#include <unistd.h>
#else
#include <conio.h>
#endif

#include "mediator.h"
#include "logger.h"
#include "program_options.h"
#include "version.h"

using namespace std;

int main(int argc, char* argv[])
{
	// Загружем параметры командной строки
	POptions::inst().load(argc, argv);
	
	LOG("Appication started, version: %s (%s)", VERSION, BUILD_TYPE);
	{
		Mediator mediator;
		mediator.start();
		
		set_exit_sig_handlers();
		mediator.wait_exit();
	}
	LOG("Applicatiom stopped");
	return 0;
}


