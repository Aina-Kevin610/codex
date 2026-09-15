#ifndef CODEXION_H
# define CODEXION_H

# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>

# include "parsing.h"
# include "utils.h"

typedef struct s_coder		t_coder;
typedef struct s_request	t_request;
typedef struct s_all		t_all;

typedef struct t_scheduler
{
	int			fifo;
	int			edf;
}	t_scheduler;

typedef struct dongle
{
	int				id;
	pthread_mutex_t	lock;
	pthread_cond_t	cond;
}	t_dongle;

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

typedef struct s_coder
{
	int				id;
	int				is_burnout;
	int				compile_done;
	int				step;
	int				have_compiled;
	int				have_debug;
	int				have_refact;
	int				dongle_hold;
	pthread_t		thread;
	t_dongle		*dongle;
	t_coder			*next;
	t_coder			*prev;
	long long		last_compile_start;
	t_all			*all;
}	t_coder;

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