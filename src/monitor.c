#include "philo.h"

unsigned long get_time_ms(void)
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void precise_usleep(long time_in_ms)
{
	long	start;

	start = get_time_ms();
	while (get_time_ms() - start < time_in_ms)
		usleep (100);
}
