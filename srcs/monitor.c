/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: airandri <airandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/02 01:19:57 by airandri          #+#    #+#             */
/*   Updated: 2026/10/02 01:37:03 by airandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/codexion.h"

int	check_burnout(t_coder *coders)
{
	int		i;
	long	now;

	i = 0;
	while (i < coders->all->arguments->coders)
	{
		now = timestamp(coders[i].all->start_time);
		if (now - coders[i].last_compile_start > coders->all->arguments->burnout)
		{
			pthread_mutex_lock(&coders[i].all->stop_mutex);
			coders[i].all->is_burnout = 1;
			pthread_mutex_unlock(&coders[i].all->stop_mutex);
			pthread_cond_broadcast(&coders->dongle_left->dongle_cond);
			pthread_cond_broadcast(&coders->dongle_right->dongle_cond);
			print_log(&coders[i], 5);
			return (1);
		}
		i++;
	}
	return (0);
}

void	*monitor(void *arg)
{
	t_coder	*coder;

	coder = (t_coder *)arg;
	while (1)
	{
		if (check_burnout(coder) || all_finished(coder))
			break ;
		usleep(1000);
	}
	return (NULL);
}
