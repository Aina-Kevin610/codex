/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: airandri <airandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/17 15:01:09 by airandri          #+#    #+#             */
/*   Updated: 2026/09/17 15:01:10 by airandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/codexion.h"

void	heap_push(t_request data, t_request **heap, t_dongle *dongle)
{
    t_request	*new_request;

    if (!heap || !dongle || dongle->heap_size >= 2)
        return ;
    new_request = malloc(sizeof(t_request));
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
    heap[0] = heap[1];
    heap[1] = NULL;
    dongle->heap_size--;
    return (tmp);
}

int	request(t_coder *coder, t_dongle *dongle)
{
	t_request	new_request;

	if (!coder || !dongle)
		return (0);
	pthread_mutex_lock(&coder->all->gle_lock);
	new_request.id_coder = coder->id;
	new_request.created_at = get_actual_time();
    new_request.deadline = coder->last_compile_start + coder->all->arguments->burnout;
	heap_push(new_request, dongle->request, dongle);
    if (dongle->heap_size == 2)
    {
        heapify(&coder->all->arguments->scheduler, dongle);
    }
	pthread_mutex_unlock(&coder->all->gle_lock);
	return (1);
}

void    heapify(t_scheduler *scheduler, t_dongle *dongle)
{
    if (scheduler->fifo == 1)
        fifo_sort(*dongle->request);
    else if (scheduler->edf == 1)
        edf_sort(*dongle->request);
    else
        fprintf(stderr, "WARNING - invalide scheduler!");
}

void    fifo_sort(t_request *request)
{
    t_request   tmp;

    if (request[0].created_at < request[1].created_at)
    {
        tmp = request[0];
        request[0] = request[1];
        request[1] = tmp;
    }
}

void    edf_sort(t_request *request)
{
    t_request   tmp;

    if (request[0].deadline > request[1].deadline)
    {
        tmp = request[0];
        request[0] = request[1];
        request[1] = tmp;
    }
}
