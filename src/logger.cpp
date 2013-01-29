#include "logger.h"

#include <stdio.h>
#include <stdarg.h>
#include "program_options.h"


void Log::note(const char* class_name, const char* format, ...)
{
	char msg[1024];			

	va_list marker;
	va_start (marker, format);
	vsnprintf(msg, 1024, format, marker);
	va_end(marker);

	printf ("[N][%s] %s\n", class_name, msg);
}

void Log::error(const char* class_name, const char* format, ...)
{
	char msg[1024];			

	va_list marker;
	va_start (marker, format);
	vsnprintf(msg, 1024, format, marker);
	va_end(marker);

	printf ("[E][%s] %s\n", class_name, msg);
}