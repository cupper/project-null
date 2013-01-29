#pragma once

extern const char* VERSION;

#ifdef NDEBUG
	const char* const BUILD_TYPE = "RELEASE";
#else
	const char* const BUILD_TYPE = "DEBUG";
#endif
