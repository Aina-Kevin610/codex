/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: airandri <airandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/02 02:05:26 by airandri          #+#    #+#             */
/*   Updated: 2026/10/15 18:34:34 by airandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_coder t_coder;
typedef struct s_request t_request;
typedef struct s_all t_all;

typedef struct s_scheduler
{
	int	fifo;
	int	edf;
} t_scheduler;

typedef struct s_request
{
	int			id_coder;
	long long	created_at;
	long long	deadline;
} t_request;

typedef struct s_dongle
{
	int				id;
	int				used_by;
	long long		free_at;
	pthread_mutex_t	dongle_lock;
	pthread_cond_t	dongle_cond;
	int				heap_size;
	t_request		heap[2];
} t_dongle;

typedef struct s_args
{
	int			coders;
	int			burnout;
	int			compile;
	int			debug;
	int			refactor;
	int			nb_compiles;
	int			dongle_cooldown;
	int			error;
	t_scheduler	scheduler;
} t_args;

typedef struct s_coder
{
	int			id;
	int			compile_done;
	int			step;
	int			finished;
	int			blocked;
	t_all		*all;
	t_dongle	*dongle_left;
	t_dongle	*dongle_right;
	long long	last_compile_start;
	pthread_t	thread;
} t_coder;

typedef struct s_all
{
	int				stop;
	int				finished_coders;
	t_args			*arguments;
	t_coder			*coder;
	t_dongle		*dongle;
	long long		start_time;
	pthread_t		monitor;
	pthread_mutex_t	gle_lock;
	pthread_cond_t	gle_cond;
	pthread_mutex_t	lock;
} t_all;

int			is_stopped(t_all *all);
int			all_finished(t_coder *coder);
void		wake_all(t_all *all);
void		reset_clock(t_all *all);
void		*monitor(void *all_ptr);
void		ft_sleep(t_all *all, long long ms);
void		lock_pair(t_dongle *a, t_dongle *b);
void		unlock_pair(t_dongle *a, t_dongle *b);
long long	get_actual_time(void);
long long	timestamp(long long start);
int			arg_check(int argc, char *argv[], t_all *all);
int			number_check(char *number, int allow_zero);
void		assign_arg(char **init, t_args *arg);
int			check_arg(char **arg);
t_args		parsing(char **argv, t_args *arg);
int			is_digit(char c);
int			init_all(t_all *all);
int			ft_error(char *message);
int			init_coder(t_all *all);
int			init_dongle(t_all *all);
void		free_simulation(t_all *all);
void		*process(void *coders);
int			start_simulation(t_all *all);
void		print_log(t_coder *coder, int step);
int			compile(t_coder *coder);
int			debug(t_coder *coder);
int			refactor(t_coder *coder);
int			take_dongle(t_coder *coder);
void		release_dongle(t_coder *coder);
int			request(t_coder *coder, t_dongle *dongle);
int			add_requests(t_coder *coder);
void		heap_push(t_dongle *dongle, t_request data, t_scheduler *scheduler);
void		heap_remove(t_dongle *dongle, int id_coder,
				t_scheduler *scheduler);
void		sift_up(t_dongle *dongle, int i, t_scheduler *scheduler);
void		sift_down(t_dongle *dongle, int i, t_scheduler *scheduler);

#endif
