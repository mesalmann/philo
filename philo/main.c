/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesalman <mesalman@student.42istanbul.com  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 13:30:46 by mesalman          #+#    #+#             */
/*   Updated: 2026/05/13 00:00:00 by mesalman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_usage(int ac)
{
	if (ac != 5 && ac != 6)
	{
		write(1, "Usage: ./philo count time_to_die ", 33);
		write(1, "time_to_eat time_to_sleep [meals]\n", 34);
		return (1);
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_table	t;

	if (check_usage(ac) || read_args(&t, av) || dinner_prep(&t))
		return (1);
	start_dinner(&t);
	cleanup(&t);
	return (0);
}
