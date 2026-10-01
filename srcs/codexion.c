/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: airandri <airandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/01 19:24:09 by airandri          #+#    #+#             */
/*   Updated: 2026/10/01 19:24:10 by airandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/codexion.h"

int	main(int argc, char *argv[])
{
	t_all	all;

	if (!init_all(&all))
		return (ft_error("allocation or synchronization initialization failed"));
	if (arg_check(argc, argv, &all))
	{
		ft_error("invalid arguments");
		free_simulation(&all);
		return (1);
	}
	if (!init_dongle(&all) || !init_coder(&all))
	{
		ft_error("allocation error");
		free_simulation(&all);
		return (1);
	}
	if (start_simulation(&all))
	{
		ft_error("problem on simulation");
		free_simulation(&all);
		return (1);
	}
	free_simulation(&all);
	return (0);
}
