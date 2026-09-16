#ifndef UTILS_H 
# define UTILS_H

typedef struct s_all	t_all;
typedef struct s_coder	t_coder;

int	    	is_digit(char c);
void	    init_all(t_all *all);
int	    	ft_error(char *message);
void	    print_coders(t_all *all);
void	    print_requests(t_coder *coder);
long long	get_actual_time(void);

#endif