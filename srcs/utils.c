/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: airandri <airandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/02 02:04:48 by airandri          #+#    #+#             */
/*   Updated: 2026/10/13 09:19:34 by airandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/codexion.h"

int	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

int	ft_error(char *message)
{
	return (fprintf(stderr, "Error - %s\n", message));
}

int	init_all(t_all *all)
{
	if (!all)
		return (0);
	memset(all, 0, sizeof(*all));
	all->arguments = malloc(sizeof(t_args));
	if (!all->arguments)
		return (0);
	all->start_time = get_actual_time();
	if (pthread_mutex_init(&all->gle_lock, NULL) != 0)
		return (0);
	if (pthread_cond_init(&all->gle_cond, NULL) != 0)
	{
		pthread_mutex_destroy(&all->gle_lock);
		return (0);
	}
	if (pthread_mutex_init(&all->lock, NULL) != 0)
	{
		pthread_cond_destroy(&all->gle_cond);
		pthread_mutex_destroy(&all->gle_lock);
		return (0);
	}
	return (1);
}
