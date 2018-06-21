#include <stdlib.h>
#include <stdio.h>

#include "clocky.h"

void check_test(int cond, const char* desc)
{
	if (cond)
	{
		printf(" [  OK  ] %s\n", desc);
	}
	else
	{
		printf(" [ FAIL ] %s\n", desc);
		exit(1);
	}
}

int main(int argc, char* argv[])
{
	(void)argc;
	(void)argv;

	printf("Running clocky test suite...\n\n");

	clocky_init();
	check_test(1, "clocky_init() succeeds");

	const uint64_t freq = clocky_get_freq();
	check_test(freq > 0, "clocky_get_freq() returns nonzero");

	clocky_sleep(10);
	check_test(1, "clocky_sleep(10) succeeds");

	const uint64_t timestamp_a = clocky_get_timestamp();
	check_test(timestamp_a > 0, "clocky_get_timestamp() => timestamp_a: returns nonzero");

	clocky_sleep(250);
	const uint64_t timestamp_b = clocky_get_timestamp();
	check_test(timestamp_b > timestamp_a, "clocky_get_timestamp() => timestamp_b: returns greater than timestamp_a");
	
	const uint64_t quarter_freq = (uint64_t)(freq * 0.25);
	const uint64_t quarter_freq_error = (uint64_t)(quarter_freq * 0.05);
	const uint64_t range_lo = quarter_freq - quarter_freq_error;
	const uint64_t range_hi = quarter_freq + quarter_freq_error;
	const uint64_t interval = timestamp_b - timestamp_a;
	check_test(interval > range_lo && interval < range_hi, "timestamps separated by a 250ms sleep are equal to (clocky_get_freq() * 0.25), +/- 5%");

	const double elapsed = clocky_get_elapsed(timestamp_a, timestamp_b);
	check_test(elapsed > 0.24 && elapsed < 0.26, "clocky_get_elapsed(timestamp_a, timestamp_b) is equal to 0.25 sec, +/- 0.01 sec");

	printf("\nAll tests passed.\n");
	return 0;
}
