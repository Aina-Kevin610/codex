#ifndef CODER_H
#define CODER_H

typedef struct s_all	t_all;
typedef struct s_coder	t_coder;

int 	init_coder(t_all *all);
int     init_dongle(t_all *all);
int	    act(t_coder *coder);
void	*process(void *coders);
void	start_simulation(t_all *all);
void	request(t_coder *coder);
void	take_dongle(t_coder *coder);
void	release_dongle(t_coder *coder);

#endif