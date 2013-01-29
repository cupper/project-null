#pragma once

#define ENTRY __PRETTY_FUNCTION__

class Log
{
public:
	static void error(const char* class_name, const char *format, ...);
	static void note(const char* class_name, const char *format, ...);
};

#define LOG_0(s)	;
#define LOG_1(s) Log::note(ENTRY, s)
#define LOG_2(s, p1) Log::note(ENTRY, s, p1)
#define LOG_3(s, p1, p2) Log::note(ENTRY, s, p1, p2)
#define LOG_4(s, p1, p2, p3) Log::note(ENTRY, s, p1, p2, p3)
#define LOG_5(s, p1, p2, p3, p4) Log::note(ENTRY, s, p1, p2, p3, p4)

#define LOG_X(x,s,p1,p2,p3,p4,FUNC, ...)  FUNC
#define LOG(...) LOG_X(,##__VA_ARGS__,\
					LOG_5(__VA_ARGS__),\
					LOG_4(__VA_ARGS__),\
					LOG_3(__VA_ARGS__),\
					LOG_2(__VA_ARGS__),\
					LOG_1(__VA_ARGS__),\
					LOG_0(__VA_ARGS__)\
				)

#define LOG_ERR_0(s)
#define LOG_ERR_1(s) Log::error(ENTRY, s)
#define LOG_ERR_2(s, p1) Log::error(ENTRY, s, p1)
#define LOG_ERR_3(s, p1, p2) Log::error(ENTRY, s, p1, p2)
#define LOG_ERR_4(s, p1, p2, p3) Log::error(ENTRY, s, p1, p2, p3)
#define LOG_ERR_5(s, p1, p2, p3, p4) Log::error(ENTRY, s, p1, p2, p3, p4)

#define LOG_ERR_X(x,s,p1,p2,p3,p4,FUNC, ...)  FUNC
#define LOG_ERR(...) LOG_ERR_X(,##__VA_ARGS__,\
					LOG_ERR_5(__VA_ARGS__),\
					LOG_ERR_4(__VA_ARGS__),\
					LOG_ERR_3(__VA_ARGS__),\
					LOG_ERR_2(__VA_ARGS__),\
					LOG_ERR_1(__VA_ARGS__),\
					LOG_ERR_0(__VA_ARGS__)\
					)

