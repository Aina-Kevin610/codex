#include "../headers/codexion.h"

static int	find_deadline(t_all *all, long long *deadline, int *coder_id)
{
	int		i;
	long long	now;
	long long	current;

	now = get_actual_time();
	*deadline = 0;
	*coder_id = 0;
	i = 0;
	while (i < all->arguments->coders)
	{
		if (all->coder[i].finished)
		{
			i++;
			continue ;
		}
		current = all->coder[i].last_compile_start
			+ all->arguments->burnout;
		if (!*deadline || current < *deadline)
		{
			*deadline = current;
			*coder_id = all->coder[i].id;
		}
		if (current <= now)
			return (1);
		i++;
	}
	return (0);
}

void	*monitor(void *all_ptr)
{
	t_all		*all;
	struct timespec	ts;
	long long	deadline;
	int			coder_id;
	int			i;

	all = (t_all *)all_ptr;
	pthread_mutex_lock(&all->gle_lock);
	while (!all->stop)
	{
		if (find_deadline(all, &deadline, &coder_id))
		{
			all->is_burnout = 1;
			all->stop = 1;
			i = 0;
			while (i < all->arguments->coders)
			{
				if (all->coder[i].id == coder_id)
				{
					print_log(&all->coder[i], 5);
					break ;
				}
				i++;
			}
			pthread_cond_broadcast(&all->gle_cond);
			break ;
		}
		ts.tv_sec = deadline / 1000;
		ts.tv_nsec = (deadline % 1000) * 1000000;
		pthread_cond_timedwait(&all->gle_cond, &all->gle_lock, &ts);
	}
	pthread_mutex_unlock(&all->gle_lock);
	return (NULL);
}
