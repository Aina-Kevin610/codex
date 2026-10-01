/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: airandri <airandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/02 00:43:17 by airandri          #+#    #+#             */
/*   Updated: 2026/10/02 01:28:48 by airandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/codexion.h"

void	print_log(t_coder *coder, int step)
{
	pthread_mutex_lock(&coder->all->lock);
	// if (coder->all->is_burnout)
	// {
	// 	pthread_mutex_unlock(&coder->all->lock);
	// 	return ;
	// }
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
	coder->last_compile_start = get_actual_time();
	pthread_mutex_unlock(&coder->all->gle_lock);
	print_log(coder, 1);
	usleep(coder->all->arguments->compile * 1000);
	coder->compile_done++;
	coder->step = 2;
	return (1);
}

int	debug(t_coder *coder)
{
	print_log(coder, 2);
	usleep(coder->all->arguments->debug * 1000);
	coder->step = 3;
	return (1);
}

int	refactor(t_coder *coder)
{
	print_log(coder, 3);
	usleep(coder->all->arguments->refactor * 1000);
	coder->step = 1;
	return (1);
}
