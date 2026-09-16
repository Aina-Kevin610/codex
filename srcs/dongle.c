#include "../headers/codexion.h"

static int	am_i_priority(t_coder *coder, t_dongle *dongle)
{
	if (!dongle || !dongle->request[0])
		return (0);
	if (coder->id != dongle->request[0]->id_coder)
		return (0);
	if (dongle->used_by != 0)
		return (0);
	if (get_actual_time() < dongle->free_at)
		return (0);
	return (1);
}

void	take_dongle(t_coder *coder)
{
	struct timespec	ts;
	long long		deadline;

	pthread_mutex_lock(&coder->all->gle_lock);
	while (!am_i_priority(coder, coder->dongle_left)
		|| !am_i_priority(coder, coder->dongle_right))
	{
		deadline = coder->dongle_left->free_at;
		if (coder->dongle_right->free_at > deadline)
			deadline = coder->dongle_right->free_at;
		if (deadline > get_actual_time())
		{
			ts.tv_sec = deadline / 1000;
			ts.tv_nsec = (deadline % 1000) * 1000000;
			pthread_cond_timedwait(&coder->all->gle_cond, &coder->all->gle_lock, &ts);
		}
		else
			pthread_cond_wait(&coder->all->gle_cond, &coder->all->gle_lock);
	}
	coder->dongle_left->used_by = coder->id;
	coder->dongle_right->used_by = coder->id;
	heap_pop(coder->dongle_left, coder->dongle_left->request);
	heap_pop(coder->dongle_right, coder->dongle_right->request);
	print_log(coder, 4);
	pthread_mutex_unlock(&coder->all->gle_lock);
}

void	release_dongle(t_coder *coder)
{
	pthread_mutex_lock(&coder->all->gle_lock);
	coder->dongle_left->used_by = 0;
	coder->dongle_right->used_by = 0;
    coder->dongle_left->free_at  = get_actual_time() + coder->all->arguments->dongle_cooldown;
    coder->dongle_right->free_at = get_actual_time() + coder->all->arguments->dongle_cooldown;
	pthread_cond_broadcast(&coder->all->gle_cond);
	pthread_mutex_unlock(&coder->all->gle_lock);
}
