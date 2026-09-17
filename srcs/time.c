/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: airandri <airandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/17 15:01:19 by airandri          #+#    #+#             */
/*   Updated: 2026/09/17 15:01:20 by airandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/codexion.h"

long long	get_actual_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((long long)time.tv_sec * 1000 + time.tv_usec / 1000);
}

long long   timestamp(long long start)
{
    return (get_actual_time() - start);
}
