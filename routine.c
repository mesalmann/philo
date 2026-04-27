#include "philo.h"

static int	ate_enough(t_philo *philo)
{
	int	done;

	if (philo->program->must_eat == -1)
		return (0);
	pthread_mutex_lock(&philo->mutex);
	done = philo->eat_count >= philo->program->must_eat;
	pthread_mutex_unlock(&philo->mutex);
	return (done);
}

static void	grab_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->right_fork->mutex);
		log_action(philo, "has taken a fork");
		pthread_mutex_lock(&philo->left_fork->mutex);
		log_action(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&philo->left_fork->mutex);
		log_action(philo, "has taken a fork");
		pthread_mutex_lock(&philo->right_fork->mutex);
		log_action(philo, "has taken a fork");
	}
}

static void	philo_eat(t_philo *philo)
{
	grab_forks(philo);
	pthread_mutex_lock(&philo->mutex);
	philo->last_meal = get_time_ms();
	philo->eat_count++;
	pthread_mutex_unlock(&philo->mutex);
	log_action(philo, "is eating");
	ft_usleep(philo->program->time_to_eat, philo->program);
	pthread_mutex_unlock(&philo->left_fork->mutex);
	pthread_mutex_unlock(&philo->right_fork->mutex);
}

static void	philo_rest(t_philo *philo)
{
	log_action(philo, "is sleeping");
	ft_usleep(philo->program->time_to_sleep, philo->program);
	log_action(philo, "is thinking");
	if (philo->program->philo_count % 2 == 1)
		ft_usleep(philo->program->time_to_eat, philo->program);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->program->philo_count == 1)
	{
		log_action(philo, "has taken a fork");
		ft_usleep(philo->program->time_to_die, philo->program);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		usleep(1000);
	while (!is_stopped(philo->program) && !ate_enough(philo))
	{
		philo_eat(philo);
		if (!ate_enough(philo))
			philo_rest(philo);
	}
	return (NULL);
}