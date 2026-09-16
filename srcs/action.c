#include "../headers/codexion.h"

void	print_log(t_coder *coder, int step)
{
	pthread_mutex_lock(&(coder->all->lock));
	if (step == 1)
	{
		fprintf(stdout, "%lld %d is compiling \n",
			get_actual_time() - coder->all->start_time, coder->id);
	}
	else if (step == 2)
	{
		fprintf(stdout, "%lld %d is debugging\n",
			get_actual_time() - coder->all->start_time, coder->id);
	}
	else if (step == 3)
	{
		fprintf(stdout, "%lld %d is refactoring\n",
			get_actual_time() - coder->all->start_time, coder->id);
	}
	else if (step == 4)
	{
		fprintf(stdout, "%lld %d has taken a dongle\n",
			get_actual_time() - coder->all->start_time, coder->id);
	}
	else
		printf("none\n");
	pthread_mutex_unlock(&(coder->all->lock));
}

int	compile(t_coder *coder)
{
	if (coder->compile_done >= coder->all->arguments->nb_compiles)
		return (0);
	if (coder->step == 1)
	{
		usleep(coder->all->arguments->compile * 1000);
		print_log(coder, coder->step);
		coder->compile_done++;
		coder->step = 2;
		return (1);
	}
	return (0);
}

int	debug(t_coder *coder)
{
	if (coder->step == 2)
	{
		usleep(coder->all->arguments->compile * 1000);
		print_log(coder, coder->step);
		coder->step = 3;
		return (1);
	}
	return (0);
}

int	refactor(t_coder *coder)
{
	if (coder->step == 3)
	{
		usleep(coder->all->arguments->compile * 1000);
		print_log(coder, coder->step);
		coder->step = 1;
		return (1);
	}
	return (0);
}
