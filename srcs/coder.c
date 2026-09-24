#include "../headers/codexion.h"

int	init_coder(t_all *all)
{
	int	i;

	all->coder = malloc(sizeof(t_coder) * all->arguments->coders);
	if (!all->coder)
		return (0);
	i = 0;
	while (i < all->arguments->coders)
	{
		all->coder[i].id = i + 1;
		all->coder[i].compile_done = 0;
		all->coder[i].step = 1;
		all->coder[i].finished = 0;
		all->coder[i].all = all;
		all->coder[i].last_compile_start = all->start_time;
		all->coder[i].dongle_left = &all->dongle[i];
		all->coder[i].dongle_right = &all->dongle[(i + 1)
			% all->arguments->coders];
		i++;
	}
	return (1);
}

int	init_dongle(t_all *all)
{
	int	i;

	all->dongle = malloc(sizeof(t_dongle) * all->arguments->coders);
	if (!all->dongle)
		return (0);
	i = 0;
	while (i < all->arguments->coders)
	{
		all->dongle[i].id = i + 1;
		all->dongle[i].heap_size = 0;
		all->dongle[i].used_by = 0;
		all->dongle[i].free_at = all->start_time;
		all->dongle[i].request[0] = NULL;
		all->dongle[i].request[1] = NULL;
		if (pthread_mutex_init(&all->dongle[i].dongle_lock, NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&all->dongle[i].dongle_lock);
			free(all->dongle);
			all->dongle = NULL;
			return (0);
		}
		i++;
	}
	return (1);
}

void	free_simulation(t_all *all)
{
	int	i;

	if (!all)
		return ;
	free_requests(all);
	if (all->dongle && all->arguments)
	{
		i = 0;
		while (i < all->arguments->coders)
		{
			pthread_mutex_destroy(&all->dongle[i].dongle_lock);
			i++;
		}
	}
	free(all->coder);
	free(all->dongle);
	free(all->arguments);
	pthread_mutex_destroy(&all->lock);
	pthread_cond_destroy(&all->gle_cond);
	pthread_mutex_destroy(&all->gle_lock);
}
