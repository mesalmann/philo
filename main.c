#include "philo.h"

void	exit_error(char *msg)
{
	printf("Error: %s\n", msg);
	exit(EXIT_FAILURE);
}

static int	is_digits_only(char *s)
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
	return (1);
}

static int	str_to_int(char *s)
{
	long	result;
	int		i;

	result = 0;
	i = 0;
	while (s[i])
	{
		if (result > (long)INT_MAX / 10)
			exit_error("argument too large");
		result = result * 10 + (s[i] - '0');
		if (result > INT_MAX)
			exit_error("argument too large");
		i++;
	}
	return ((int)result);
}

void	parse_args(t_table *t, char **av)
{
	int	i;

	i = 1;
	while (av[i])
	{
		if (!is_digits_only(av[i]))
			exit_error("invalid argument");
		i++;
	}
	t->philo_count = str_to_int(av[1]);
	t->time_to_die = str_to_int(av[2]);
	t->time_to_eat = str_to_int(av[3]);
	t->time_to_sleep = str_to_int(av[4]);
	if (!t->philo_count || !t->time_to_die
		|| !t->time_to_eat || !t->time_to_sleep)
		exit_error("invalid argument");
	t->meal_limit = -1;
	if (av[5])
	{
		t->meal_limit = str_to_int(av[5]);
		if (t->meal_limit <= 0)
			exit_error("meal limit must be a positive integer");
	}
}

int	main(int ac, char **av)
{
	t_table	t;

	if (ac != 5 && ac != 6)
	{
		printf("Usage: ./philo count time_to_die ");
		printf("time_to_eat time_to_sleep [meals]\n");
		return (1);
	}
	parse_args(&t, av);
	init_table(&t);
	launch_sim(&t);
	cleanup(&t);
	return (0);
}
