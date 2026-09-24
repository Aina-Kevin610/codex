#ifndef DONGLE_H
# define DONGLE_H

typedef struct s_coder t_coder;

int		take_dongle(t_coder *coder);
void	release_dongle(t_coder *coder);

#endif
