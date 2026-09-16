#include "../headers/codexion.h"
 
int	act(t_coder *coder)
{
	int	signal;

	signal = 1;
	coder->step = 1;
	request(coder, coder->dongle_left);
	request(coder, coder->dongle_right);
	take_dongle(coder);
    signal *= compile(coder);
	release_dongle(coder);
    signal *= debug(coder);
    signal *= refactor(coder);
    return (signal);
}

void	*process(void *coders)
{
	int		check;

	if (!coders)
	{
		fprintf(stderr, "ERROR - Processing failed");
		return (NULL);
	}
	check = 1;
	while (check)
		check = act((t_coder *)coders);
	return (NULL);
}

void	start_simulation(t_all *all)
{
	int	i;

	if (!all || !all->coder || !all->arguments
		|| all->arguments->coders <= 0)
		return ;
	i = 0;
	while (i < all->arguments->coders)
	{
		pthread_create(&all->coder[i].thread, NULL, process,
			(void *)&all->coder[i]);
		i++;
	}
	i = 0;
	while (i < all->arguments->coders)
	{
		pthread_join(all->coder[i].thread, NULL);
		i++;
	}
}
