#include "../headers/codexion.h"

int	main(int argc, char *argv[])
{
	t_all	all;
	init_all(&all);
	if (arg_check(argc, argv, &all))
	{
		ft_error("ERROR - Invalid arguments!");
		return (1);
	}
	return (0);
}
