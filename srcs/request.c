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

void	heap_push(t_request data, t_request **heap, t_dongle *dongle)
{
	t_request	*new_request;

	if (!heap || !dongle || dongle->heap_size >= 2)
		return ;
	new_request = malloc(sizeof(*new_request));
	if (!new_request)
		return ;
	*new_request = data;
	heap[dongle->heap_size] = new_request;
	dongle->heap_size++;
}

t_request	*heap_pop(t_dongle *dongle, t_request **heap)
{
	t_request	*tmp;

	if (!dongle || !heap || dongle->heap_size <= 0)
		return (NULL);
	tmp = heap[0];
	if (dongle->heap_size == 2)
		heap[0] = heap[1];
	heap[dongle->heap_size - 1] = NULL;
	dongle->heap_size--;
	return (tmp);
}

void	heapify(t_scheduler *scheduler, t_dongle *dongle)
{
	if (scheduler->fifo)
		fifo_sort(dongle->request);
	else if (scheduler->edf)
		edf_sort(dongle->request);
}

void	fifo_sort(t_request *request[2])
{
	t_request	*tmp;

	if (request[0] && request[1]
		&& request[0]->created_at > request[1]->created_at)
	{
		tmp = request[0];
		request[0] = request[1];
		request[1] = tmp;
	}
}

void	edf_sort(t_request *request[2])
{
	t_request	*tmp;

	if (request[0] && request[1]
		&& (request[0]->deadline > request[1]->deadline
			|| (request[0]->deadline == request[1]->deadline
				&& request[0]->id_coder > request[1]->id_coder)))
	{
		tmp = request[0];
		request[0] = request[1];
		request[1] = tmp;
	}
}
