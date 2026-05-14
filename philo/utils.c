/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesalman <mesalman@student.42istanbul.com  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 13:31:17 by mesalman          #+#    #+#             */
/*   Updated: 2026/05/12 13:31:18 by mesalman         ###   ########.fr       */
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
	long	remaining;

	end_time = ms_now() + ms;
	while (!sim_over(t))
	{
		remaining = end_time - ms_now();
		if (remaining <= 0)
			break ;
		if (remaining > 5)
			usleep(1000);
		else if (remaining > 1)
			usleep(200);
		else
			usleep(50);
	}
}

void	print_state(t_philo *p, char *msg)
{
	int		stopped;
	long	ts;

	pthread_mutex_lock(&p->table->write_lock);
	if (philo_dead_now(p))
	{
		pthread_mutex_unlock(&p->table->write_lock);
		return ;
	}
	ts = ms_now() - p->table->start_ms;
	pthread_mutex_lock(&p->table->stop_lock);
	stopped = p->table->stop_flag;
	pthread_mutex_unlock(&p->table->stop_lock);
	if (!stopped)
		printf("%ld %d %s\n", ts, p->id, msg);
	pthread_mutex_unlock(&p->table->write_lock);
}

void	print_death(t_philo *p)
{
	pthread_mutex_lock(&p->table->write_lock);
	pthread_mutex_lock(&p->table->stop_lock);
	p->table->stop_flag = 1;
	pthread_mutex_unlock(&p->table->stop_lock);
	printf("%ld %d died\n", ms_now() - p->table->start_ms, p->id);
	pthread_mutex_unlock(&p->table->write_lock);
}

int	sim_over(t_table *t)
{
	int	flag;

	pthread_mutex_lock(&t->stop_lock);
	flag = t->stop_flag;
	pthread_mutex_unlock(&t->stop_lock);
	return (flag);
}
