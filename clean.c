#include "philo.h"

static void	join_threads(t_program *program)
{
	int	i;

	i = 0;
	while (i < program->philo_count)
	{
		pthread_join(program->philos[i].thread, NULL);
		i++;
	}
}

static void	destroy_mutexes(t_program *program)
{
	int	i;

	i = 0;
	while (i < program->philo_count)
	{
		pthread_mutex_destroy(&program->forks[i].mutex);
		pthread_mutex_destroy(&program->philos[i].mutex);
		i++;
	}
	pthread_mutex_destroy(&program->stop_mutex);
	pthread_mutex_destroy(&program->print_mutex);
}

void	clean(t_program *program)
{
	join_threads(program);
	destroy_mutexes(program);
	free(program->forks);
	free(program->philos);
}