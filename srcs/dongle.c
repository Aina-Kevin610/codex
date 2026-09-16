#include "../headers/codexion.h"
#include <pthread.h>

static int  am_i_priority(t_coder *coder, t_dongle *dongle)
{
    if (!dongle || !dongle->request[0])
        return (0);
    if (coder->id == dongle->request[0]->id_coder && dongle->used_by == 0)
        return (1);
    return (0);
}

void	take_dongle(t_coder *coder)
{
	pthread_mutex_lock(&coder->all->gle_lock);
	while (!am_i_priority(coder, coder->dongle_left)
		|| !am_i_priority(coder, coder->dongle_right))
		pthread_cond_wait(&coder->all->gle_cond, &coder->all->gle_lock);
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
	pthread_cond_broadcast(&coder->all->gle_cond);
	pthread_mutex_unlock(&coder->all->gle_lock);
}