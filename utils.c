/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesalman <mesalman@student.42istanbul.com  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 13:31:17 by mesalman          #+#    #+#             */
/*   Updated: 2026/05/05 13:31:18 by mesalman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ms_now(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000L + tv.tv_usec / 1000);
}

void	sleep_ms(long ms, t_table *t)
{
	long	end_time;

	end_time = ms_now() + ms;
	while (ms_now() < end_time)
	{
		if (sim_over(t))
			break ;
		usleep(200);
	}
}

void	print_state(t_philo *p, char *msg)
{
	pthread_mutex_lock(&p->table->write_lock);
	if (!p->table->stop_flag)
		printf("%ld %d %s\n",
			ms_now() - p->table->start_ms, p->id, msg);
	pthread_mutex_unlock(&p->table->write_lock);
}

void	print_death(t_philo *p)
{
	pthread_mutex_lock(&p->table->write_lock);
	p->table->stop_flag = 1;
	printf("%ld %d died\n",
		ms_now() - p->table->start_ms, p->id);
	pthread_mutex_unlock(&p->table->write_lock);
}

int	sim_over(t_table *t)
{
	int	flag;

	//* hepsine ayrı mutex
	pthread_mutex_lock(&t->write_lock);
	flag = t->stop_flag;
	pthread_mutex_unlock(&t->write_lock);
	return (flag);
}
