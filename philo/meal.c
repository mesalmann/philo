/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meal.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesalman <mesalman@student.42istanbul.com  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 13:31:09 by mesalman          #+#    #+#             */
/*   Updated: 2026/05/13 00:00:00 by mesalman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	reach_for_forks(t_philo *p)
{
	t_fork	*first;
	t_fork	*second;

	/* kucuk id'li catal once: deadlock onlenir */
	first = p->left_fork;
	second = p->right_fork;
	if (p->left_fork->id > p->right_fork->id)
	{
		first = p->right_fork;
		second = p->left_fork;
	}
	pthread_mutex_lock(&first->mutex);
	if (sim_over(p->table))
	{
		pthread_mutex_unlock(&first->mutex);
		return (1);
	}
	print_state(p, "has taken a fork");
	pthread_mutex_lock(&second->mutex);
	print_state(p, "has taken a fork");
	pthread_mutex_lock(&p->lock);
	p->last_meal_ms = ms_now();
	pthread_mutex_unlock(&p->lock);
	return (0);
}

void	eat(t_philo *p)
{
	if (reach_for_forks(p))
		return ;
	print_state(p, "is eating");
	sleep_ms(p->table->meal_ms, p->table);
	pthread_mutex_lock(&p->lock);
	p->meal_count++;
	pthread_mutex_unlock(&p->lock);
	pthread_mutex_unlock(&p->left_fork->mutex);
	pthread_mutex_unlock(&p->right_fork->mutex);
}

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
