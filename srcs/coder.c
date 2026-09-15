#include "../headers/codexion.h"

int	init_coder(t_all *all)
{
	int		i;
	t_coder	*coder;

    coder = (t_coder *) malloc(sizeof(t_coder) * all->arguments->coders);
    if (!coder)
        return (0);
    i = 0;
    while(i < all->arguments->coders)
    {
        i++;
        coder[i].id = i;
        coder[i].compile_done = 0;
        coder[i].all = all;
        coder[i].is_burnout = 0;
        coder[i].dongle_left = NULL;
        coder[i].dongle_right = NULL;
        coder[i].last_compile_start = 0;
    }
    return (1);
}
