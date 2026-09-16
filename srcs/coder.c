#include "../headers/codexion.h"

int	init_coder(t_all *all)
{
	int		i;
	t_coder	*coder;

	coder = (t_coder *)malloc(sizeof(t_coder) * all->arguments->coders);
	if (!coder)
		return (0);
	all->coder = coder;
	i = 0;
	while (i < all->arguments->coders)
	{
		coder[i].id = i + 1;
		coder[i].compile_done = 0;
		coder[i].all = all;
		coder[i].is_burnout = 0;
		coder[i].last_compile_start = 0;
		coder[i].dongle_left = &all->dongle[i];
		coder[i].dongle_right = &all->dongle[(i + 1)
			% all->arguments->coders];
		i++;
	}
	return (1);
}

int	init_dongle(t_all *all)
{
	int		    i;
	t_dongle	*dongle;

    dongle = (t_dongle *) malloc(sizeof(t_dongle) * all->arguments->coders);
    if (!dongle)
        return (0);
    all->dongle = dongle;
    i = 0;
    while (i < all->arguments->coders)
    {
        dongle[i].id = i + 1;
		dongle[i].heap_size = 0;
		dongle[i].used_by = 0;
		dongle[i].request[0] = NULL;
		dongle[i].request[1] = NULL;
        i++;
    }
    return (1);
}