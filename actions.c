#include "philo.h"

static int	simulation_stopped(t_program *program)
{
	int	stop;

	pthread_mutex_lock(&program->stop_mutex);
	stop = program->stop;
	pthread_mutex_unlock(&program->stop_mutex);
	return (stop);
}

void	print_status(t_philo *philo, char *status)
{
	long	time;

	pthread_mutex_lock(&philo->program->print_mutex);
	if (!simulation_stopped(philo->program))
	{
		time = get_time_ms() - philo->program->start_time;
		printf("%ld %d %s\n", time, philo->id, status);
	}
	pthread_mutex_unlock(&philo->program->print_mutex);
}

void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->right_fork->mutex);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(&philo->left_fork->mutex);
		print_status(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&philo->left_fork->mutex);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(&philo->right_fork->mutex);
		print_status(philo, "has taken a fork");
	}
}

void	eat(t_philo *philo)
{
	take_forks(philo);
	pthread_mutex_lock(&philo->mutex);
	philo->last_meal = get_time_ms();
	philo->eat_count++;
	pthread_mutex_unlock(&philo->mutex);
	print_status(philo, "is eating");
	ft_usleep(philo->program->time_to_eat, philo->program);
	pthread_mutex_unlock(&philo->left_fork->mutex);
	pthread_mutex_unlock(&philo->right_fork->mutex);
}

void	sleep_and_think(t_philo *philo)
{
	print_status(philo, "is sleeping");
	ft_usleep(philo->program->time_to_sleep, philo->program);
	print_status(philo, "is thinking");
	if (philo->program->philo_count % 2 == 1)
		ft_usleep(philo->program->time_to_eat, philo->program);
}