# ifndef CODEXION_H
# define CODEXION_H

# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
#include "parsing.h"

typedef struct s_coder		t_coder;
typedef struct s_request	t_request;
typedef struct s_all		t_all;

typedef struct t_scheduler
{
	int			fifo;
	int			edf;
}	t_scheduler;

typedef struct s_args
{
	int				coders;
	int				burnout;
	int				compile;
	int				debug;
	int				refactor;
	int				nb_compiles;
	int				dongle_cooldown;
	int				error;
	t_scheduler		scheduler;
}	t_args;

typedef struct s_all
{
	t_args			*arguments;
	t_coder			*coder;
	int				stop;
	long long		start_time;
	pthread_mutex_t	lock;
	pthread_cond_t	cond;
}	t_all;

# endif