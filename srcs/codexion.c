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
	init_coder(&all);
	print_coders(all.coder, all.arguments->coders);
	return (0);
}
