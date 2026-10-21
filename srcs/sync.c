/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sync.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: airandri <airandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/02 02:04:40 by airandri          #+#    #+#             */
/*   Updated: 2026/10/21 22:32:18 by airandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/codexion.h"

int	is_stopped(t_all *all)
{
	int	stop;

	pthread_mutex_lock(&all->lock);
	stop = all->stop;
	pthread_mutex_unlock(&all->lock);
	return (stop);
}

void	wake_all(t_all *all)
{
	int	i;

	i = 0;
	while (i < all->arguments->coders)
	{
		pthread_mutex_lock(&all->dongle[i].dongle_lock);
		pthread_cond_broadcast(&all->dongle[i].dongle_cond);
		pthread_mutex_unlock(&all->dongle[i].dongle_lock);
		i++;
	}
}

void	lock_pair(t_dongle *a, t_dongle *b)
{
	if (a == b)
		pthread_mutex_lock(&a->dongle_lock);
	else if (a->id < b->id)
	{
		pthread_mutex_lock(&a->dongle_lock);
		pthread_mutex_lock(&b->dongle_lock);
	}
	else
	{
		pthread_mutex_lock(&b->dongle_lock);
		pthread_mutex_lock(&a->dongle_lock);
	}
}

void	unlock_pair(t_dongle *a, t_dongle *b)
{
	pthread_mutex_unlock(&a->dongle_lock);
	if (a != b)
		pthread_mutex_unlock(&b->dongle_lock);
}
