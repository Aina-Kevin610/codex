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

static int	before(t_request *a, t_request *b, t_scheduler *sch)
{
	if (sch->edf && a->deadline != b->deadline)
		return (a->deadline < b->deadline);
	if (sch->fifo && a->created_at != b->created_at)
		return (a->created_at < b->created_at);
	return (a->id_coder < b->id_coder);
}

static void	swap_req(t_request *a, t_request *b)
{
	t_request	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	sift_up(t_dongle *d, int i, t_scheduler *sch)
{
	while (i > 0 && before(&d->heap[i], &d->heap[(i - 1) / 2], sch))
	{
		swap_req(&d->heap[i], &d->heap[(i - 1) / 2]);
		i = (i - 1) / 2;
	}
}

void	sift_down(t_dongle *d, int i, t_scheduler *sch)
{
	int	child;

	while (2 * i + 1 < d->heap_size)
	{
		child = 2 * i + 1;
		if (child + 1 < d->heap_size
			&& before(&d->heap[child + 1], &d->heap[child], sch))
			child++;
		if (!before(&d->heap[child], &d->heap[i], sch))
			break ;
		swap_req(&d->heap[child], &d->heap[i]);
		i = child;
	}
}

void	heap_push(t_dongle *d, t_request data, t_scheduler *sch)
{
	if (d->heap_size >= 2)
		return ;
	d->heap[d->heap_size] = data;
	d->heap_size++;
	sift_up(d, d->heap_size - 1, sch);
}
