/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesalman <mesalman@student.42istanbul.com  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 13:31:09 by mesalman          #+#    #+#             */
/*   Updated: 2026/05/13 00:00:00 by mesalman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	one_man_show(t_philo *p)
{
	pthread_mutex_lock(&p->left_fork->mutex);
	print_state(p, "has taken a fork");
	sleep_ms(p->table->starvation_ms + 1, p->table);
	pthread_mutex_unlock(&p->left_fork->mutex);
}

static void	overthink(t_philo *p)
{
	long	think_ms;

	print_state(p, "is thinking");
	if (p->table->philo_count % 2 == 0)
		return ;
	think_ms = p->table->starvation_ms
		- p->table->meal_ms - p->table->nap_ms;
	if (think_ms > 0)
		sleep_ms(think_ms / 2, p->table);
}

void	*philo_life(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	if (p->table->philo_count == 1)
	{
		one_man_show(p);
		return (NULL);
	}
	/* cift ve son tek philo: meal_ms/2 stagger ile baslangic serlestirilir */
	if (p->id % 2 == 0 || (p->table->philo_count % 2 == 1
		&& p->id == p->table->philo_count))
		sleep_ms(1, p->table);
	while (!sim_over(p->table) && !is_full(p))
	{
		eat(p);
		if (is_full(p))
			return (NULL);
		print_state(p, "is sleeping");
		sleep_ms(p->table->nap_ms, p->table);
		if (sim_over(p->table))
			return (NULL);
		overthink(p);
	}
	return (NULL);
}
