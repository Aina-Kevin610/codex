#ifndef CODER_H
# define CODER_H

typedef struct s_all t_all;
typedef struct s_coder t_coder;

int		init_coder(t_all *all);
int		init_dongle(t_all *all);
void		free_simulation(t_all *all);
void		*process(void *coders);
int		start_simulation(t_all *all);

#endif
