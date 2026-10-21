#include <pthread.h>
#include <stdio.h>

pthread_mutex_t	lock = PTHREAD_MUTEX_INITIALIZER;
int				counter = 0;

void	*routine(void *arg)
{
	(void)arg;
	for (int i = 0; i < 100000; i++)
	{
		pthread_mutex_lock(&lock);
        counter++;
		pthread_mutex_unlock(&lock);
	}

	return (NULL);
}

int	main(void)
{
	pthread_t	t1;
	pthread_t	t2;

	pthread_create(&t1, NULL, routine, NULL);
	pthread_create(&t2, NULL, routine, NULL);
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	printf("counter = %d\n", counter);
	return (0);
}