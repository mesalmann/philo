/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesalman <mesalman@student.42istanbul.com  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 13:31:09 by mesalman          #+#    #+#             */
/*   Updated: 2026/05/05 13:31:10 by mesalman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	grab_forks(t_philo *p)
{
	t_fork	*first;
	t_fork	*second;

	if (p->left_fork->id < p->right_fork->id)
	{
		first = p->left_fork;
		second = p->right_fork;
	}
	else
	{
		first = p->right_fork;
		second = p->left_fork;
	}
	pthread_mutex_lock(&first->mutex);
	print_state(p, "has taken a fork");
	//* biri sadece 1 çatal aldıktan sonra diğeri öldüyse bu philo çatal bekliyor program sonsuza kadar çalışıyor
	pthread_mutex_lock(&second->mutex);
	print_state(p, "has taken a fork");
}

static void	eat(t_philo *p)
{
	grab_forks(p);
	pthread_mutex_lock(&p->lock);
	p->last_meal_ms = ms_now();
	p->meal_count++;
	pthread_mutex_unlock(&p->lock);
	print_state(p, "is eating");
	sleep_ms(p->table->meal_ms, p->table);
	pthread_mutex_unlock(&p->left_fork->mutex);
	pthread_mutex_unlock(&p->right_fork->mutex);
}

static void	one_philo(t_philo *p)
{
	pthread_mutex_lock(&p->left_fork->mutex);
	print_state(p, "has taken a fork");
	sleep_ms(p->table->starvation_ms + 1, p->table);
	pthread_mutex_unlock(&p->left_fork->mutex);
}

static void	cycle(t_philo *p)
{
	eat(p);
	if (is_full(p))
		return ;
	print_state(p, "is sleeping");
	sleep_ms(p->table->nap_ms, p->table);
	if (sim_over(p->table))
		return ;
	print_state(p, "is thinking");
	//* tabledan yeme süresine ulaşıyo
	if (p->table->philo_count % 2 == 1)
		sleep_ms(p->table->meal_ms, p->table);
}

void	*philo_life(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	//* Table kısmı bütün philolar tarafından erişildiğinden data race oluyor.
	if (p->table->philo_count == 1)
	{
		one_philo(p);
		return (NULL);
	}
	//* Table kısmı bütün philolar tarafından erişildiğinden data race oluyor.
	if (p->id % 2 == 0 || (p->table->philo_count % 2 == 1
			&& p->id == p->table->philo_count))
		sleep_ms(p->table->meal_ms, p->table);
	while (!sim_over(p->table) && !is_full(p))
		cycle(p);
	return (NULL);
}
