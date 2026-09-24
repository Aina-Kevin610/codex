/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: airandri <airandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/17 15:02:19 by airandri          #+#    #+#             */
/*   Updated: 2026/09/24 16:17:46 by airandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/codexion.h"

int	is_digit(char c)
{
	return (c <= '9' && c >= '0');
}

int	ft_error(char *message)
{
	int	result;

	result = fprintf(stderr, "Error - %s", message);
	return (result);
}

void	init_all(t_all *all)
{
	t_args	*arguments;

	arguments = (t_args *) malloc(sizeof(t_args));
	if (!arguments)
	{
		ft_error("ERROR - Allocation error");
		return ;
	}
	all->arguments = arguments;
	all->start_time = get_actual_time();
	all->coder = NULL;
	all->stop = 0;
	all->is_burnout = 0;
	pthread_mutex_init(&all->m_lock, NULL);
	pthread_cond_init(&all->m_cond, NULL);
	pthread_mutex_init(&all->lock, NULL);
	pthread_cond_init(&all->cond, NULL);
	pthread_mutex_init(&all->gle_lock, NULL);
	pthread_cond_init(&all->gle_cond, NULL);
	pthread_create(&all->monitor, NULL, monitor, (void *)all);
}

void	print_coders(t_all *all)
{
	int	i;

	if (!all || !all->coder || !all->arguments
		|| all->arguments->coders <= 0)
	{
		printf("No coder found");
		return ;
	}
	i = 0;
	while (i < all->arguments->coders)
	{
		printf("coder_id: %d | dongle_left_id: %d | dongle_right_id: %d\n",
			all->coder[i].id,
			all->coder[i].dongle_left ? all->coder[i].dongle_left->id : 0,
			all->coder[i].dongle_right ? all->coder[i].dongle_right->id : 0);
		i++;
	}
}


static void	print_request_id(t_request *request)
{
	if (request)
		printf("%d", request->id_coder);
	else
		printf("-");
}

void	print_requests(t_coder *coder)
{
	if (!coder)
	{
		printf("coder: empty\n");
		return ;
	}
	printf("(%d)[", coder->dongle_left->id);
	if (coder->dongle_left)
	{
		print_request_id(coder->dongle_left->request[0]);
		printf(", ");
		print_request_id(coder->dongle_left->request[1]);
	}
	else
		printf("-, -");
	printf("] (%d)[", coder->dongle_right->id);
	if (coder->dongle_right)
	{
		print_request_id(coder->dongle_right->request[0]);
		printf(", ");
		print_request_id(coder->dongle_right->request[1]);
	}
	else
		printf("-, -");
	printf("]\n");
}
