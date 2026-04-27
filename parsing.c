#include "philo.h"

int	ft_atoi(char *s)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	while (s[i])
	{
		if (res > INT_MAX / 10)
			error_exit("Invalid argument");
		if (res == INT_MAX / 10 && s[i] - '0' > INT_MAX % 10)
			error_exit("Invalid argument");
		res = res * 10 + s[i] - '0';
		i++;
	}
	return (res);
}

void	parse_arg(t_program *program, char **av)
{
	program->philo_count = ft_atoi(av[1]);
	program->time_to_die = ft_atoi(av[2]);
	program->time_to_eat = ft_atoi(av[3]);
	program->time_to_sleep = ft_atoi(av[4]);
	program->must_eat = -1;
	if (av[5])
		program->must_eat = ft_atoi(av[5]);
}