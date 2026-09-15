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

void	print_coders(t_coder *coder, int coder_count)
{
	int	i;

	if (!coder || coder_count <= 0)
	{
		printf("No coder found");
		return ;
	}
	i = 0;
	while (i < coder_count)
	{
		printf("coder_id: %d\n", coder[i].id);
		i++;
	}
}
