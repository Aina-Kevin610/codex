/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: airandri <airandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/02 01:32:55 by airandri          #+#    #+#             */
/*   Updated: 2026/10/02 01:32:56 by airandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	take_one(t_coder *coder, t_dongle *dongle)
{
	pthread_mutex_lock(&dongle->dongle_lock);
	struct timespec	ts;

	while (!am_i_priority(coder, dongle))
	{
		if (dongle->free_at > get_actual_time())
		{
			ts.tv_sec = dongle->free_at / 1000;
			ts.tv_nsec = (dongle->free_at % 1000) * 1000000;
			pthread_cond_timedwait(&dongle->dongle_cond, &dongle->dongle_lock, &ts);
		}
		else
			pthread_cond_wait(&dongle->dongle_cond, &dongle->dongle_lock);
	}
	dongle->used_by = coder->id;
	heap_pop(dongle, dongle->request);
	print_log(coder, 4);
	pthread_mutex_unlock(&dongle->dongle_lock);
}

int	take_dongle(t_coder *coder)
{
	if (coder->id % 2)
	{
		take_one(coder, coder->dongle_left);
		take_one(coder, coder->dongle_right);
	}
	else
	{
		take_one(coder, coder->dongle_right);
		take_one(coder, coder->dongle_left);
	}
	return (1);
}

void	release_dongle(t_coder *coder)
{
	long long	now;

	pthread_mutex_lock(&coder->dongle_left->dongle_lock);
	pthread_mutex_lock(&coder->dongle_right->dongle_lock);
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
	pthread_cond_broadcast(&coder->dongle_left->dongle_cond);
	pthread_cond_broadcast(&coder->dongle_right->dongle_cond);
	pthread_mutex_unlock(&coder->dongle_left->dongle_lock);
	pthread_mutex_unlock(&coder->dongle_right->dongle_lock);
}
