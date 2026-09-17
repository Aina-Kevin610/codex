/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: airandri <airandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/17 14:32:40 by airandri          #+#    #+#             */
/*   Updated: 2026/09/17 14:32:41 by airandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/codexion.h"
 
int	act(t_coder *coder)
{
	int	signal;

	signal = 1;
	coder->step = 1;
	pthread_mutex_lock(&coder->dongle_left->dongle_lock);
	request(coder, coder->dongle_left);
	pthread_mutex_unlock(&coder->dongle_left->dongle_lock);
	pthread_mutex_lock(&coder->dongle_right->dongle_lock);
	request(coder, coder->dongle_right);
	pthread_mutex_unlock(&coder->dongle_right->dongle_lock);
	take_dongle(coder);
    signal *= compile(coder);
	release_dongle(coder);
    signal *= debug(coder);
    signal *= refactor(coder);
    return (signal);
}

void	*process(void *coders)
{
	int		check;

	if (!coders)
	{
		fprintf(stderr, "ERROR - Processing failed");
		return (NULL);
	}
	check = 1;
	while (check)
		check = act((t_coder *)coders);
	return (NULL);
}

void	start_simulation(t_all *all)
{
	int	i;

	if (!all || !all->coder || !all->arguments
		|| all->arguments->coders <= 0)
		return ;
	i = 0;
	while (i < all->arguments->coders)
	{
		pthread_create(&all->coder[i].thread, NULL, process,
			(void *)&all->coder[i]);
		i++;
	}
	i = 0;
	while (i < all->arguments->coders)
	{
		pthread_join(all->coder[i].thread, NULL);
		i++;
	}
}
