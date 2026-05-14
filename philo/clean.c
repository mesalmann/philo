/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesalman <mesalman@student.42istanbul.com  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 13:30:36 by mesalman          #+#    #+#             */
/*   Updated: 2026/05/13 00:00:00 by mesalman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	prep_fail(t_table *t, int stage)
{
	if (stage >= 3)
		destroy_forks(t);
	if (stage >= 2)
	{
		pthread_mutex_destroy(&t->stop_lock);
		pthread_mutex_destroy(&t->write_lock);
	}
	free(t->forks);
	free(t->philos);
	return (1);
}

void	destroy_forks(t_table *t)
{
	int	i;

	i = 0;
	while (i < t->philo_count)
	{
		pthread_mutex_destroy(&t->forks[i].mutex);
		i++;
	}
}

void	cleanup(t_table *t)
{
	int	i;

	i = 0;
	while (i < t->threads_started)
	{
		pthread_join(t->philos[i].thread, NULL);
		i++;
	}
	i = 0;
	while (i < t->philo_count)
	{
		pthread_mutex_destroy(&t->philos[i].lock);
		i++;
	}
	destroy_forks(t);
	pthread_mutex_destroy(&t->write_lock);
	pthread_mutex_destroy(&t->stop_lock);
	free(t->forks);
	free(t->philos);
}
