/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: airandri <airandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/02 02:05:38 by airandri          #+#    #+#             */
/*   Updated: 2026/10/13 09:20:54 by airandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUEST_H
# define REQUEST_H

typedef struct s_coder t_coder;
typedef struct s_request t_request;
typedef struct s_dongle t_dongle;
typedef struct s_scheduler t_scheduler;

int		request(t_coder *coder, t_dongle *dongle);
int		add_requests(t_coder *coder);
void	heap_push(t_dongle *d, t_request data, t_scheduler *sch);
void	heap_remove(t_dongle *d, int id_coder, t_scheduler *sch);
void	sift_up(t_dongle *d, int i, t_scheduler *sch);
void	sift_down(t_dongle *d, int i, t_scheduler *sch);

#endif
