/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: airandri <airandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/17 14:32:44 by airandri          #+#    #+#             */
/*   Updated: 2026/09/17 14:32:45 by airandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODER_H
#define CODER_H

typedef struct s_all	t_all;
typedef struct s_coder	t_coder;

int 	init_coder(t_all *all);
int     init_dongle(t_all *all);
int	    act(t_coder *coder);
void	*process(void *coders);
void	start_simulation(t_all *all);

#endif