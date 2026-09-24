#include "../headers/codexion.h"

int	arg_check(int argc, char *argv[], t_all *all)
{
	if (argc != 9)
		return (1);
	*(all->arguments) = parsing(argv, all->arguments);
	return (all->arguments->error);
}

int	number_check(char *number)
{
	long long	value;
	int		i;

	if (!number || !number[0])
		return (0);
	value = 0;
	i = 0;
	while (number[i])
	{
		if (!is_digit(number[i]))
			return (0);
		value = value * 10 + (number[i] - '0');
		if (value > 2147483647)
			return (0);
		i++;
	}
	return (value > 0);
}

void	assign_arg(char **init, t_args *arg)
{
	arg->coders = atoi(init[1]);
	arg->burnout = atoi(init[2]);
	arg->compile = atoi(init[3]);
	arg->debug = atoi(init[4]);
	arg->refactor = atoi(init[5]);
	arg->nb_compiles = atoi(init[6]);
	arg->dongle_cooldown = atoi(init[7]);
	arg->scheduler.fifo = !strcmp(init[8], "fifo");
	arg->scheduler.edf = !strcmp(init[8], "edf");
}

t_args	parsing(char **argv, t_args *arg)
{
	if (check_arg(argv))
	{
		assign_arg(argv, arg);
		arg->error = 0;
	}
	else
		arg->error = 1;
	return (*arg);
}

int	check_arg(char **arg)
{
	int	i;

	i = 1;
	while (i <= 7)
	{
		if (!number_check(arg[i]))
			return (0);
		i++;
	}
	return (!strcmp(arg[8], "fifo") || !strcmp(arg[8], "edf"));
}
