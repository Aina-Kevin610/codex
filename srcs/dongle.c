/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: airandri <airandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/02 01:32:55 by airandri          #+#    #+#             */
/*   Updated: 2026/10/21 19:38:35 by airandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/codexion.h"

static int	ready(t_coder *coder, t_dongle *dongle)
{
	t_coder	*head;

	if (dongle->heap_size == 0 || dongle->used_by != 0)
		return (0);
	if (get_actual_time() < dongle->free_at)
		return (0);
	if (dongle->heap[0].id_coder == coder->id)
		return (1);
	head = &coder->all->coder[dongle->heap[0].id_coder - 1];
	return (head->blocked);
}

static void	wait_blocker(t_coder *coder, t_dongle *blocker, t_dongle *other)
{
	struct timespec	ts;

	coder->blocked = !(blocker->used_by == 0 && blocker->heap_size > 0
			&& blocker->heap[0].id_coder == coder->id);
	if (other != blocker)
	{
		pthread_cond_broadcast(&other->dongle_cond);
		pthread_mutex_unlock(&other->dongle_lock);
	}
	if (blocker->used_by == 0 && blocker->free_at > get_actual_time())
	{
		ts.tv_sec = blocker->free_at / 1000;
		ts.tv_nsec = (blocker->free_at % 1000) * 1000000;
		pthread_cond_timedwait(&blocker->dongle_cond,
			&blocker->dongle_lock, &ts);
	}
	else
		pthread_cond_wait(&blocker->dongle_cond, &blocker->dongle_lock);
	pthread_mutex_unlock(&blocker->dongle_lock);
}

static void	grab(t_coder *coder)
{
	t_scheduler	*sch;

	sch = &coder->all->arguments->scheduler;
	coder->dongle_left->used_by = coder->id;
	heap_remove(coder->dongle_left, coder->id, sch);
	if (coder->dongle_right != coder->dongle_left)
	{
		coder->dongle_right->used_by = coder->id;
		heap_remove(coder->dongle_right, coder->id, sch);
	}
}

int	able(t_coder *coder)
{
	pthread_mutex_lock(&coder->dongle_left->dongle_lock);
	if (!coder->dongle_left->used_by && !coder->dongle_left->used_by)
	{
		pthread_mutex_unlock(&coder->dongle_left->dongle_lock);
		return (1);
	}
	pthread_mutex_unlock(&coder->dongle_left->dongle_lock);
	return(0);
}

int	take_dongle(t_coder *coder)
{
	t_dongle	*l;
	t_dongle	*r;

	l = coder->dongle_left;
	r = coder->dongle_right;
	while (1)
	{
		lock_pair(l, r);
		coder->blocked = 0;
		if (is_stopped(coder->all))
		{
			unlock_pair(l, r);
			return (0);
		}
		if (ready(coder, l) && ready(coder, r))
		{
			grab(coder);
			unlock_pair(l, r);
			return (1);
		}
		if (!ready(coder, l))
			wait_blocker(coder, l, r);
		else
			wait_blocker(coder, r, l);
	}
}

void	release_dongle(t_coder *coder)
{
	long long	now;

	lock_pair(coder->dongle_left, coder->dongle_right);
	now = get_actual_time();
	coder->dongle_left->used_by = 0;
	coder->dongle_left->free_at = now + coder->all->arguments->dongle_cooldown;
	if (coder->dongle_right != coder->dongle_left)
	{
		coder->dongle_right->used_by = 0;
		coder->dongle_right->free_at = now
			+ coder->all->arguments->dongle_cooldown;
	}
	pthread_cond_broadcast(&coder->dongle_left->dongle_cond);
	pthread_cond_broadcast(&coder->dongle_right->dongle_cond);
	unlock_pair(coder->dongle_left, coder->dongle_right);
}
