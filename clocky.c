#include "clocky.h"

#ifdef _WIN32
#include <windows.h>
#else
#include <time.h>
#endif

static uint64_t s_freq = 0;

void clocky_init()
{
#ifdef _WIN32
	LARGE_INTEGER val;
	if (QueryPerformanceFrequency(&val))
	{
		s_freq = val.QuadPart;
	}
#else
#endif
}

uint64_t clocky_get_freq()
{
	return s_freq;
}

uint64_t clocky_get_timestamp()
{
#ifdef _WIN32
	LARGE_INTEGER val;
	if (QueryPerformanceCounter(&val))
	{
		return val.QuadPart;
	}
	return 0;
#else
	return 0;
#endif
}

double clocky_get_elapsed(uint64_t from_timestamp, uint64_t to_timestamp)
{
	if (s_freq)
	{
		return (double)(to_timestamp - from_timestamp) / s_freq;
	}
	return 0.0;
}

void clocky_sleep(int milliseconds)
{
#ifdef _WIN32
	Sleep(milliseconds);
#else
#endif
}
