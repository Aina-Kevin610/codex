/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: airandri <airandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/02 01:19:57 by airandri          #+#    #+#             */
/*   Updated: 2026/10/28 18:29:19 by airandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/codexion.h"

static int	has_burned(t_all *all, int i)
{
	long long	last;
	int			done;

	pthread_mutex_lock(&all->gle_lock);
	last = all->coder[i].last_compile_start;
	done = all->coder[i].compile_done >= all->arguments->nb_compiles;
	pthread_mutex_unlock(&all->gle_lock);
	if (done)
		return (0);
	return (get_actual_time() - last >= all->arguments->burnout);
}

static void	declare_stop(t_all *all, int id)
{
	pthread_mutex_lock(&all->lock);
	if (!all->stop)
	{
		all->stop = 1;
		if (id)
			printf("%lld %d burned out\n", timestamp(all->start_time), id);
	}
	pthread_mutex_unlock(&all->lock);
	wake_all(all);
}

int	ft_is_all_finished(t_all *all)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&all->gle_lock);
	while (i < all->arguments->coders)
	{
		if (all->coder[i].compile_done < all->arguments->nb_compiles)
		{
			pthread_mutex_unlock(&all->gle_lock);
			return (0);
		}
		i++;
	}
	pthread_mutex_unlock(&all->gle_lock);
	return (1);
}

static int	check_burnout(t_all *all)
{
	int	i;

	i = 0;
	while (i < all->arguments->coders)
	{
		if (has_burned(all, i))
		{
			declare_stop(all, all->coder[i].id);
			return (1);
		}
		i++;
	}
	return (0);
}

void	*monitor(void *arg)
{
	t_all	*all;

	all = (t_all *)arg;
	while (1)
	{
		if (check_burnout(all))
			break ;
		if (ft_is_all_finished(all))
		{
			declare_stop(all, 0);
			break ;
		}
		usleep(1000);
	}
	return (NULL);
}
