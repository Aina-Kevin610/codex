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
# include "coder.h"
# include "action.h"
# include "request.h"

typedef struct s_coder		t_coder;
typedef struct s_request	t_request;
typedef struct s_all		t_all;

typedef struct t_scheduler
{
	int			fifo;
	int			edf;
}	t_scheduler;

typedef struct s_dongle
{
	int				id;
	int				heap_size;
	t_request		*request[2];
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
	t_all			*all;
	t_dongle		*dongle_left;
	t_dongle		*dongle_right;
	long long		last_compile_start;
	pthread_t		thread;
}	t_coder;

typedef struct s_request
{
	int			id_coder;
}	t_request;

typedef struct s_all
{
	t_args			*arguments;
	t_coder			*coder;
	t_dongle		*dongle;
	int				stop;
	long long		start_time;
	pthread_mutex_t	lock;
	pthread_cond_t	cond;
}	t_all;

# endif