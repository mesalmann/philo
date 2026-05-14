/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesalman <mesalman@student.42istanbul.com  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 13:30:59 by mesalman          #+#    #+#             */
/*   Updated: 2026/05/05 13:31:00 by mesalman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_dead_now(t_philo *p)
{
	long	elapsed;

	pthread_mutex_lock(&p->lock);
	elapsed = ms_now() - p->last_meal_ms;
	pthread_mutex_unlock(&p->lock);
	return (elapsed >= p->table->starvation_ms);
}

static int	has_starved(t_philo *p)
{
	long	elapsed;

	pthread_mutex_lock(&p->lock);
	elapsed = ms_now() - p->last_meal_ms;
	pthread_mutex_unlock(&p->lock);
	if (elapsed >= p->table->starvation_ms)
	{
		print_death(p);
		return (1);
	}
	return (0);
}

static int	feast_complete(t_table *t)
{
	int	i;
	int	count;

	if (t->max_meals < 0)
		return (0);
	count = 0;
	i = 0;
	while (i < t->philo_count)
	{
		pthread_mutex_lock(&t->philos[i].lock);
		if (t->philos[i].meal_count >= t->max_meals)
			count++;
		pthread_mutex_unlock(&t->philos[i].lock);
		i++;
	}
	return (count == t->philo_count);
}

static void	end_dinner(t_table *t)
{
	pthread_mutex_lock(&t->stop_lock);
	t->stop_flag = 1;
	pthread_mutex_unlock(&t->stop_lock);
}

void	monitor(t_table *t)
{
	int	i;

	while (!sim_over(t))
	{
		i = 0;
		while (i < t->philo_count)
		{
			if (has_starved(&t->philos[i]))
				return ;
			i++;
		}
		if (feast_complete(t))
		{
			end_dinner(t);
			return ;
		}
		usleep(250);
	}
}
