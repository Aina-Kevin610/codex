/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: airandri <airandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/17 14:32:26 by airandri          #+#    #+#             */
/*   Updated: 2026/09/17 14:32:27 by airandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ACTION_H
# define ACTION_H

typedef struct s_coder	t_coder;

void	print_log(t_coder *coder, int step);
int		compile(t_coder *coder);
int		debug(t_coder *coder);
int		refactor(t_coder *coder);

#endif
