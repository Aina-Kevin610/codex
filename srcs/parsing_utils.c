#include "../headers/codexion.h"

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
	all->start_time = 0;
	all->coder = NULL;
	all->stop = 0;
}

void	init_coder_id(t_coder *coder)
{
	t_coder	*tmp;
	int		i;

	if (!coder)
		return ;
	i = 1;
	tmp = coder;
	while (tmp)
	{
		tmp->id = i;
		tmp->dongle->id = i;
		tmp->dongle_hold = 0;
		tmp->compile_done = 0;
		tmp = tmp->next;
		i++;
	}
}

t_coder	*create_coder(void)
{
	t_coder		*new_coder;
	t_dongle	*new_dongle;

	new_dongle = (t_dongle *) malloc(sizeof(t_dongle));
	if (!new_dongle)
		return (NULL);
	new_coder = (t_coder *) malloc(sizeof(t_coder));
	if (!new_coder)
	{
		free(new_dongle);
		return (NULL);
	}
	pthread_mutex_init(&new_dongle->lock, NULL);
	pthread_cond_init(&new_dongle->cond, NULL);
	new_coder->dongle = new_dongle;
	new_coder->prev = NULL;
	new_coder->next = NULL;
	return (new_coder);
}

void	add_coder(t_coder *coder)
{
	t_coder	*tmp;

	if (!coder)
		return ;
	tmp = coder;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = create_coder();
	if (tmp->next)
		tmp->next->prev = tmp;
}

void	linking_coder(t_all *all)
{
	int		i;
	t_coder	*coder;
	t_coder	*last_coder;

	i = 0;
	while (i < (int)all->arguments->coders)
	{
		if (all->coder)
			add_coder(all->coder);
		else
			all->coder = create_coder();
		i++;
	}
	init_coder_id(all->coder);
	coder = all->coder;
	while (coder)
	{
		coder->all = all;
		coder = coder->next;
	}
	last_coder = all->coder;
	while (last_coder->next)
		last_coder = last_coder->next;
	all->coder->prev = last_coder;
}