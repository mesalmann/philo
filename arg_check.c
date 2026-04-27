#include "philo.h"

int	is_valid_num(char *s)
{
	int	i;

	i = 0;
	if (!s || !s[i])
		return (0);
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (0);
		i++;
	}
	if (s[0] == '0')
		return (0);
	return (1);
}

int	is_arg_valid(char **av)
{
	int	i;

	i = 1;
	while (av[i])
	{
		if (!is_valid_num(av[i]))
			return (0);
		i++;
	}
	return (1);
}