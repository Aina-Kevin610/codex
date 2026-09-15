#include "../headers/codexion.h"

int	is_digit(char c)
{
	return (c <= '9' && c >= '0');
}

int	ft_error(char *message)
{
	int	result;

	result = fprintf(stderr, "Error - %s", message);
	return (result);
}