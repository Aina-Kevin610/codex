/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: airandri <airandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/17 15:01:19 by airandri          #+#    #+#             */
/*   Updated: 2026/10/02 02:16:36 by airandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/codexion.h"

long long	get_actual_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((long long)time.tv_sec * 1000 + time.tv_usec / 1000);
}

long long	timestamp(long long start)
{
	return (get_actual_time() - start);
}

void	ft_sleep(t_all *all, long long ms)
{
	long long	end;

	end = get_actual_time() + ms;
	while (get_actual_time() < end && !is_stopped(all))
		usleep(500);
}

void	reset_clock(t_all *all)
{
	int	i;

	all->start_time = get_actual_time();
	i = 0;
	while (i < all->arguments->coders)
	{
		all->coder[i].last_compile_start = all->start_time;
		all->dongle[i].free_at = all->start_time;
		i++;
	}
}
