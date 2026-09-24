#include "../headers/codexion.h"

static int	all_finished(t_coder *coder)
{
	int	finished;

	finished = 0;
	pthread_mutex_lock(&coder->all->gle_lock);
	if (coder->compile_done >= coder->all->arguments->nb_compiles)
	{
		finished = 1;
		coder->finished = 1;
		coder->all->finished_coders++;
		if (coder->all->finished_coders == coder->all->arguments->coders)
		{
			coder->all->stop = 1;
			pthread_cond_broadcast(&coder->all->gle_cond);
		}
	}
	pthread_mutex_unlock(&coder->all->gle_lock);
	return (finished);
}

static int	add_requests(t_coder *coder)
{
	int	ok;

	ok = 1;
	pthread_mutex_lock(&coder->all->gle_lock);
	if (coder->all->stop)
		ok = 0;
	else if (!request(coder, coder->dongle_left))
		ok = 0;
	else if (coder->dongle_right != coder->dongle_left
		&& !request(coder, coder->dongle_right))
		ok = 0;
	pthread_mutex_unlock(&coder->all->gle_lock);
	return (ok);
}

void	*process(void *coders)
{
	t_coder	*coder;

	coder = (t_coder *)coders;
	if (!coder)
		return (NULL);
	while (1)
	{
		pthread_mutex_lock(&coder->all->gle_lock);
		if (coder->all->stop)
		{
			pthread_mutex_unlock(&coder->all->gle_lock);
			break ;
		}
		pthread_mutex_unlock(&coder->all->gle_lock);
		if (!add_requests(coder))
			break ;
		if (!take_dongle(coder))
			break ;
		compile(coder);
		release_dongle(coder);
		if (all_finished(coder))
			break ;
		if (!debug(coder) || !refactor(coder))
			break ;
	}
	return (NULL);
}

int	start_simulation(t_all *all)
{
	int	i;
	int	created;

	if (!all || !all->coder || !all->arguments)
		return (1);
	if (pthread_create(&all->monitor, NULL, monitor, all) != 0)
		return (1);
	created = 0;
	while (created < all->arguments->coders)
	{
		if (pthread_create(&all->coder[created].thread, NULL, process,
			&all->coder[created]) != 0)
		{
			pthread_mutex_lock(&all->gle_lock);
			all->stop = 1;
			pthread_cond_broadcast(&all->gle_cond);
			pthread_mutex_unlock(&all->gle_lock);
			break ;
		}
		created++;
	}
	i = 0;
	while (i < created)
	{
		pthread_join(all->coder[i].thread, NULL);
		i++;
	}
	pthread_mutex_lock(&all->gle_lock);
	all->stop = 1;
	pthread_cond_broadcast(&all->gle_cond);
	pthread_mutex_unlock(&all->gle_lock);
	pthread_join(all->monitor, NULL);
	return (0);
}
