#include "philo.h"

int	is_full(t_philo *p)
{
	int	done;

	if (p->table->meal_limit < 0)
		return (0);
	pthread_mutex_lock(&p->lock);
	done = (p->meals_eaten >= p->table->meal_limit);
	pthread_mutex_unlock(&p->lock);
	return (done);
}

static int	philo_died(t_philo *p)
{
	long	elapsed;

	pthread_mutex_lock(&p->lock);
	elapsed = now_ms() - p->last_meal_ms;
	pthread_mutex_unlock(&p->lock);
	if (elapsed >= p->table->time_to_die)
	{
		log_death(p);
		return (1);
	}
	return (0);
}

static int	all_ate_enough(t_table *t)
{
	int	i;
	int	count;

	if (t->meal_limit < 0)
		return (0);
	count = 0;
	i = 0;
	while (i < t->philo_count)
	{
		pthread_mutex_lock(&t->philos[i].lock);
		if (t->philos[i].meals_eaten >= t->meal_limit)
			count++;
		pthread_mutex_unlock(&t->philos[i].lock);
		i++;
	}
	return (count == t->philo_count);
}

static void	stop_sim(t_table *t)
{
	pthread_mutex_lock(&t->stop_lock);
	t->stop_flag = 1;
	pthread_mutex_unlock(&t->stop_lock);
}

void	monitor_table(t_table *t)
{
	int	i;

	while (!is_stopped(t))
	{
		i = 0;
		while (i < t->philo_count)
		{
			if (philo_died(&t->philos[i]))
				return ;
			i++;
		}
		if (all_ate_enough(t))
		{
			stop_sim(t);
			return ;
		}
		usleep(500);
	}
}
