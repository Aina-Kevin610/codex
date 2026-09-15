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
	all->start_time = 0;
	all->coder = NULL;
	all->stop = 0;
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
