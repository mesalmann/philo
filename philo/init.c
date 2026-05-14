/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesalman <mesalman@student.42istanbul.com  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 13:30:36 by mesalman          #+#    #+#             */
/*   Updated: 2026/05/13 00:00:00 by mesalman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_locks(t_table *t)
{
	if (pthread_mutex_init(&t->write_lock, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&t->stop_lock, NULL) != 0)
	{
		pthread_mutex_destroy(&t->write_lock);
		return (1);
	}
	return (0);
}

static int	set_forks(t_table *t)
{
	int	i;

	i = 0;
	while (i < t->philo_count)
	{
		t->forks[i].id = i + 1;
		if (pthread_mutex_init(&t->forks[i].mutex, NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&t->forks[i].mutex);
			return (1);
		}
		i++;
	}
	return (0);
}

static int	seat_philos(t_table *t)
{
	int	i;

	i = 0;
	while (i < t->philo_count)
	{
		t->philos[i].id = i + 1;
		t->philos[i].meal_count = 0;
		t->philos[i].last_meal_ms = 0;
		t->philos[i].table = t;
		t->philos[i].left_fork = &t->forks[i];
		t->philos[i].right_fork = &t->forks[(i + 1) % t->philo_count];
		if (pthread_mutex_init(&t->philos[i].lock, NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&t->philos[i].lock);
			return (1);
		}
		i++;
	}
	return (0);
}

int	dinner_prep(t_table *t)
{
	t->stop_flag = 0;
	t->threads_started = 0;
	t->philos = malloc(sizeof(t_philo) * t->philo_count);
	if (!t->philos)
	{
		write(2, "Error: malloc\n", 14);
		return (1);
	}
	t->forks = malloc(sizeof(t_fork) * t->philo_count);
	if (!t->forks)
	{
		write(2, "Error: malloc\n", 14);
		free(t->philos);
		return (1);
	}
	if (init_locks(t))
		return (prep_fail(t, 1));
	if (set_forks(t))
		return (prep_fail(t, 2));
	if (seat_philos(t))
		return (prep_fail(t, 3));
	return (0);
}

void	start_dinner(t_table *t)
{
	int	i;

	t->start_ms = ms_now();
	i = 0;
	while (i < t->philo_count)
	{
		t->philos[i].last_meal_ms = t->start_ms;
		if (pthread_create(&t->philos[i].thread, NULL,
				philo_life, &t->philos[i]) != 0)
		{
			pthread_mutex_lock(&t->stop_lock);
			t->stop_flag = 1;
			pthread_mutex_unlock(&t->stop_lock);
			while (--i >= 0)
				pthread_join(t->philos[i].thread, NULL);
			t->threads_started = 0;
			return ;
		}
		t->threads_started++;
		i++;
	}
	monitor(t);
}
