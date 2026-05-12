/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesalman <mesalman@student.42istanbul.com  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 13:30:46 by mesalman          #+#    #+#             */
/*   Updated: 2026/05/05 13:30:47 by mesalman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	err_msg(char *msg)
{
	int	len;

	len = 0;
	while (msg[len])
		len++;
	write(2, msg, len);
	return (1);
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
			return (-1);
		result = result * 10 + (s[i] - '0');
		if (result > INT_MAX)
			return (-1);
		i++;
	}
	return ((int)result);
}

int	read_args(t_table *t, char **av)
{
	int	i;

	i = 1;
	while (av[i] && is_digits_only(av[i]))
		i++;
	if (av[i])
		return (err_msg("Error: invalid argument\n"));
	t->philo_count = str_to_int(av[1]);
	t->starvation_ms = str_to_int(av[2]);
	t->meal_ms = str_to_int(av[3]);
	t->nap_ms = str_to_int(av[4]);
	if (t->philo_count <= 0 || t->starvation_ms <= 0
		|| t->meal_ms <= 0 || t->nap_ms <= 0)
		return (err_msg("Error: invalid argument\n"));
	t->max_meals = -1;
	if (av[5])
		t->max_meals = str_to_int(av[5]);
	if (av[5] && t->max_meals <= 0)
		return (err_msg("Error: invalid argument\n"));
	return (0);
}

int	main(int ac, char **av)
{
	t_table	t;

	if (ac != 5 && ac != 6)
	{
		write(1, "Usage: ./philo count time_to_die ", 33);
		write(1, "time_to_eat time_to_sleep [meals]\n", 34);
		return (1);
	}
	if (read_args(&t, av) || init_table(&t))
		return (1);
	launch_sim(&t);
	cleanup(&t);
	return (0);
}
