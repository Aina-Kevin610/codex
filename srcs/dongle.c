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

static void	remove_request(t_dongle *dongle, int coder_id)
{
	t_request	*request;

	if (!dongle || dongle->heap_size <= 0)
		return ;
	if (dongle->request[0] && dongle->request[0]->id_coder == coder_id)
	{
		request = heap_pop(dongle, dongle->request);
		free(request);
	}
}

int	take_dongle(t_coder *coder)
{
	struct timespec	ts;
	long long		deadline;
	t_dongle		*left;
	t_dongle		*right;

	left = coder->dongle_left;
	right = coder->dongle_right;
	pthread_mutex_lock(&coder->all->gle_lock);
	while (!coder->all->stop
		&& (!am_i_priority(coder, left)
			|| (right != left && !am_i_priority(coder, right))))
	{
		deadline = left->free_at;
		if (right->free_at > deadline)
			deadline = right->free_at;
		if (deadline > get_actual_time())
		{
			ts.tv_sec = deadline / 1000;
			ts.tv_nsec = (deadline % 1000) * 1000000;
			pthread_cond_timedwait(&coder->all->gle_cond,
				&coder->all->gle_lock, &ts);
		}
		else
			pthread_cond_wait(&coder->all->gle_cond, &coder->all->gle_lock);
	}
	if (coder->all->stop)
	{
		pthread_mutex_unlock(&coder->all->gle_lock);
		return (0);
	}
	left->used_by = coder->id;
	if (right != left)
		right->used_by = coder->id;
	remove_request(left, coder->id);
	if (right != left)
		remove_request(right, coder->id);
	coder->last_compile_start = get_actual_time();
	print_log(coder, 4);
	pthread_mutex_unlock(&coder->all->gle_lock);
	return (1);
}

void	release_dongle(t_coder *coder)
{
	long long	now;

	pthread_mutex_lock(&coder->all->gle_lock);
	now = get_actual_time();
	coder->dongle_left->used_by = 0;
	coder->dongle_left->free_at = now
		+ coder->all->arguments->dongle_cooldown;
	if (coder->dongle_right != coder->dongle_left)
	{
		coder->dongle_right->used_by = 0;
		coder->dongle_right->free_at = now
			+ coder->all->arguments->dongle_cooldown;
	}
	pthread_cond_broadcast(&coder->all->gle_cond);
	pthread_mutex_unlock(&coder->all->gle_lock);
}
