#include "philo.h"

void	log_action(t_philo *philo, char *msg)
{
	long	time;

	pthread_mutex_lock(&philo->program->print_mutex);
	if (!is_stopped(philo->program))
	{
		time = get_time_ms() - philo->program->start_time;
		printf("%ld %d %s\n", time, philo->id, msg);
	}
	pthread_mutex_unlock(&philo->program->print_mutex);
}

void	log_death(t_philo *philo)
{
	long	time;

	pthread_mutex_lock(&philo->program->print_mutex);
	if (!is_stopped(philo->program))
	{
		set_stop(philo->program);
		time = get_time_ms() - philo->program->start_time;
		printf("%ld %d died\n", time, philo->id);
	}
	pthread_mutex_unlock(&philo->program->print_mutex);
}