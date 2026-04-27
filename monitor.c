#include "philo.h"

static int	philo_is_dead(t_philo *philo)
{
	long	last_meal;
	long	now;

	pthread_mutex_lock(&philo->mutex);
	last_meal = philo->last_meal;
	pthread_mutex_unlock(&philo->mutex);
	now = get_time_ms();
	if (now - last_meal >= philo->program->time_to_die)
	{
		log_death(philo);
		return (1);
	}
	return (0);
}

static int	all_ate_enough(t_program *program)
{
	int	i;
	int	count;

	if (program->must_eat == -1)
		return (0);
	i = 0;
	count = 0;
	while (i < program->philo_count)
	{
		pthread_mutex_lock(&program->philos[i].mutex);
		if (program->philos[i].eat_count >= program->must_eat)
			count++;
		pthread_mutex_unlock(&program->philos[i].mutex);
		i++;
	}
	return (count == program->philo_count);
}

void	supervisor_loop(t_program *program)
{
	int	i;

	while (!is_stopped(program))
	{
		if (all_ate_enough(program))
		{
			set_stop(program);
			return ;
		}
		i = 0;
		while (i < program->philo_count)
		{
			if (philo_is_dead(&program->philos[i]))
				return ;
			i++;
		}
		usleep(500);
	}
}