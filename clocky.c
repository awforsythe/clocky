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
	struct timespec res;
	if (clock_getres(CLOCK_MONOTONIC, &res) == 0)
	{
		s_freq = (uint64_t)(res.tv_sec + (res.tv_nsec * 1000000000));
	}
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
	struct timespec val;
	if (clock_gettime(CLOCK_MONOTONIC, &val) == 0)
	{
		const uint64_t whole_nsec = (uint64_t)val.tv_sec * 1000000000;
		return whole_nsec + (uint64_t)val.tv_nsec;
	}
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
	struct timespec interval;
	interval.tv_sec = 0;
	interval.tv_nsec = milliseconds * 1000000;
	nanosleep(&interval, NULL);
#endif
}
