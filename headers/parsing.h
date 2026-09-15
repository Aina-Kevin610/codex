#ifndef PARSING_H
# define PARSING_H

typedef struct s_args	t_args;
typedef struct s_coder	t_coder;
typedef struct s_all	t_all;

int		arg_check(int argc, char *argv[], t_all *all);
int		number_check(char *number);
void	assign_arg(char **init, t_args *arg);
int		check_arg(char **arg);

int		is_digit(char c);
int		ft_error(char *message);
void	init_all(t_all *all);
void	init_coder_id(t_coder *coder);
void	add_coder(t_coder *coder);
void	linking_coder(t_all *all);
t_args	parsing(char **argv, t_args *arg);
t_coder	*create_coder(void);


#endif