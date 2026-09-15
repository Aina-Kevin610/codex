#ifndef UTILS_H 
# define UTILS_H

typedef struct s_all	t_all;

int	    	is_digit(char c);
void	    init_all(t_all *all);
int	    	ft_error(char *message);
void	    print_coders(t_all *all);
long long	get_actual_time(void);

#endif