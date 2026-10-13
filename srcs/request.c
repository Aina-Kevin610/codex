/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: airandri <airandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/02 02:04:55 by airandri          #+#    #+#             */
/*   Updated: 2026/10/02 02:16:10 by airandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/codexion.h"

void	heap_remove(t_dongle *d, int id_coder, t_scheduler *sch)
{
	int	i;

	i = 0;
	while (i < d->heap_size && d->heap[i].id_coder != id_coder)
		i++;
	if (i == d->heap_size)
		return ;
	d->heap_size--;
	if (i == d->heap_size)
		return ;
	d->heap[i] = d->heap[d->heap_size];
	sift_up(d, i, sch);
	sift_down(d, i, sch);
}

int	request(t_coder *coder, t_dongle *dongle)
{
	t_request	new_request;

	if (!coder || !dongle)
		return (0);
	new_request.id_coder = coder->id;
	new_request.created_at = get_actual_time();
	new_request.deadline = coder->last_compile_start
		+ coder->all->arguments->burnout;
	heap_push(dongle, new_request, &coder->all->arguments->scheduler);
	return (1);
}
