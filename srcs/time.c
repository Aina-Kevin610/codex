#include "../headers/codexion.h"

long long	get_actual_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((long long)time.tv_sec * 1000 + time.tv_usec / 1000);
}

long long   timestamp(long long start)
{
    return (get_actual_time() - start);
}
