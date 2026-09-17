/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: airandri <airandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/17 14:34:14 by airandri          #+#    #+#             */
/*   Updated: 2026/09/17 14:34:15 by airandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

typedef struct s_args	t_args;
typedef struct s_all	t_all;

int		arg_check(int argc, char *argv[], t_all *all);
int		number_check(char *number);
void	assign_arg(char **init, t_args *arg);
int		check_arg(char **arg);
t_args	parsing(char **argv, t_args *arg);

#endif