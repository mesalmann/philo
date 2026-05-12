/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watch.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesalman <mesalman@student.42istanbul.com  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 13:30:59 by mesalman          #+#    #+#             */
/*   Updated: 2026/05/05 13:31:00 by mesalman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_full(t_philo *p)
{
	int	done;

	if (p->table->max_meals < 0)
		return (0);
	pthread_mutex_lock(&p->lock);
	done = (p->meal_count >= p->table->max_meals);
	pthread_mutex_unlock(&p->lock);
	return (done);
}

static int	is_hungry(t_philo *p)
{
	long	elapsed;

	pthread_mutex_lock(&p->lock);
	elapsed = ms_now() - p->last_meal_ms;
	if (elapsed >= p->table->starvation_ms)
	{
		print_death(p);
		pthread_mutex_unlock(&p->lock);
		return (1);
	}
	pthread_mutex_unlock(&p->lock);
	return (0);
}

static int	all_full(t_table *t)
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

static void	stop(t_table *t)
{
	pthread_mutex_lock(&t->write_lock);
	t->stop_flag = 1;
	pthread_mutex_unlock(&t->write_lock);
}

void	monitor(t_table *t)
{
	int	i;

	while (!sim_over(t))
	{
		i = 0;
		while (i < t->philo_count)
		{
			if (is_hungry(&t->philos[i]))
				return ;
			i++;
		}
		if (all_full(t))
		{
			stop(t);
			return ;
		}
		usleep(500);
	}
}
