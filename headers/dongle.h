/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: airandri <airandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/17 14:32:59 by airandri          #+#    #+#             */
/*   Updated: 2026/09/17 14:33:00 by airandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DONGLE_H
# define DONGLE_H

typedef struct s_coder		t_coder;

void    take_dongle(t_coder *coder);
void    release_dongle(t_coder *coder);

#endif
