/**
	This is a quick-and-dirty, source-only, cross-platform library for accessing high-resolution timestamps.
*/
#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/** Initializes the library: should be called before any other clocky functions. No cleanup is required. */
void clocky_init();

/** Returns the frequency of the timestamps returned by clocky_get_timestamp.  */
uint64_t clocky_get_freq();

/** Returns a timestamp value representing the current time. */
uint64_t clocky_get_timestamp();

/** Returns the current clock time in seconds. */
double clocky_get_time();

/** Returns the real time elapsed between two timestamps, in seconds. */
double clocky_get_elapsed(uint64_t from_timestamp, uint64_t to_timestamp);

/** Suspends execution of the calling thread for the specified interval. */
void clocky_sleep(int milliseconds);

#ifdef __cplusplus
}
#endif
