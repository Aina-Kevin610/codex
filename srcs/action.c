/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: airandri <airandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/02 00:43:17 by airandri          #+#    #+#             */
/*   Updated: 2026/10/21 19:37:29 by airandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/codexion.h"

void	print_log(t_coder *coder, int step)
{
	pthread_mutex_lock(&coder->all->lock);
	if (coder->all->stop)
	{
		pthread_mutex_unlock(&coder->all->lock);
		return ;
	}
	if (step == 1)
		fprintf(stdout, "%lld %d is compiling\n",
			timestamp(coder->all->start_time), coder->id);
	else if (step == 2)
		fprintf(stdout, "%lld %d is debugging\n",
			timestamp(coder->all->start_time), coder->id);
	else if (step == 3)
		fprintf(stdout, "%lld %d is refactoring\n",
			timestamp(coder->all->start_time), coder->id);
	else if (step == 4)
		fprintf(stdout, "%lld %d has taken a dongle\n",
			timestamp(coder->all->start_time), coder->id);
	else if (step == 5)
		fprintf(stdout, "%lld %d burned out\n",
			timestamp(coder->all->start_time), coder->id);
	pthread_mutex_unlock(&coder->all->lock);
}

int	compile(t_coder *coder)
{
	pthread_mutex_lock(&coder->all->gle_lock);
	coder->last_compile_start = get_actual_time() + coder->all->arguments->compile;
	pthread_mutex_unlock(&coder->all->gle_lock);
	print_log(coder, 1);
	ft_sleep(coder->all, coder->all->arguments->compile);
	pthread_mutex_lock(&coder->all->gle_lock);
	coder->compile_done++;
	pthread_mutex_unlock(&coder->all->gle_lock);
	coder->step = 2;
	return (1);
}

int	debug(t_coder *coder)
{
	print_log(coder, 2);
	ft_sleep(coder->all, coder->all->arguments->debug);
	coder->step = 3;
	return (1);
}

int	refactor(t_coder *coder)
{
	print_log(coder, 3);
	ft_sleep(coder->all, coder->all->arguments->refactor);
	coder->step = 1;
	return (1);
}
