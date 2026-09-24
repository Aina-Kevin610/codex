/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: airandri <airandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/24 14:12:20 by airandri          #+#    #+#             */
/*   Updated: 2026/09/24 14:48:12 by airandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/codexion.h"

void    *monitor(void *all_ptr)
{
    t_all   *all;

    all = (t_all *)all_ptr;
    pthread_mutex_lock(&all->m_lock);
    while(!all->is_burnout || !all->stop)
        pthread_cond_wait(&all->m_cond, &all->m_lock);
    printf("burned out");
    pthread_mutex_unlock(&all->m_lock);
    return (NULL);
}