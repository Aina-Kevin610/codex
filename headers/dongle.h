/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: airandri <airandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/02 02:05:32 by airandri          #+#    #+#             */
/*   Updated: 2026/10/02 02:05:33 by airandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DONGLE_H
# define DONGLE_H

typedef struct s_coder t_coder;

int		take_dongle(t_coder *coder);
void	release_dongle(t_coder *coder);

#endif
