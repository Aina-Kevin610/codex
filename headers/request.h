/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: airandri <airandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/17 14:34:19 by airandri          #+#    #+#             */
/*   Updated: 2026/09/17 14:34:20 by airandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUEST_H
# define REQUEST_H

typedef struct s_coder	    t_coder;
typedef struct s_request	t_request;
typedef struct s_dongle 	t_dongle;
typedef struct s_scheduler 	t_scheduler;

int         request(t_coder *coder, t_dongle *dongle);
void        heap_push(t_request data, t_request **heap, t_dongle *dongle);
t_request   *heap_pop(t_dongle *dongle, t_request **heap);

void        fifo_sort(t_request *request);
void        edf_sort(t_request *request);
void        heapify(t_scheduler *scheduler, t_dongle *dongle);

#endif
