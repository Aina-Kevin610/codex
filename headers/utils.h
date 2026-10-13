/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: airandri <airandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/02 02:05:41 by airandri          #+#    #+#             */
/*   Updated: 2026/10/02 02:05:51 by airandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

typedef struct s_all t_all;
typedef struct s_coder t_coder;

int			is_digit(char c);
int			init_all(t_all *all);
int			ft_error(char *message);

#endif
