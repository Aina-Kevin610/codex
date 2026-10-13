/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: airandri <airandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/02 02:03:37 by airandri          #+#    #+#             */
/*   Updated: 2026/10/13 09:20:39 by airandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/codexion.h"

int	all_finished(t_coder *coder)
{
	int	finished;

	pthread_mutex_lock(&coder->all->gle_lock);
	finished = coder->compile_done >= coder->all->arguments->nb_compiles;
	pthread_mutex_unlock(&coder->all->gle_lock);
	return (finished);
}

int	add_requests(t_coder *coder)
{
	int	ok;

	ok = 1;
	lock_pair(coder->dongle_left, coder->dongle_right);
	if (is_stopped(coder->all))
		ok = 0;
	else if (!request(coder, coder->dongle_left))
		ok = 0;
	else if (coder->dongle_right != coder->dongle_left
		&& !request(coder, coder->dongle_right))
		ok = 0;
	unlock_pair(coder->dongle_left, coder->dongle_right);
	return (ok);
}

void	*process(void *coders)
{
	t_coder	*coder;

	coder = (t_coder *)coders;
	if (!coder)
		return (NULL);
	while (!is_stopped(coder->all))
	{
		if (!add_requests(coder) || !take_dongle(coder))
			break ;
		compile(coder);
		release_dongle(coder);
		if (all_finished(coder) || is_stopped(coder->all))
			break ;
		debug(coder);
		refactor(coder);
	}
	return (NULL);
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
