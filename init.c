#include "philo.h"

static void	init_forks(t_program *program)
{
	int	i;

	i = 0;
	while (i < program->philo_count)
	{
		pthread_mutex_init(&program->forks[i].mutex, NULL);
		i++;
	}
}

static void	init_one_philo(t_program *program, int i)
{
	program->philos[i].id = i + 1;
	program->philos[i].eat_count = 0;
	program->philos[i].last_meal = 0;
	program->philos[i].left_fork = &program->forks[i];
	program->philos[i].right_fork = &program->forks[(i + 1)
		% program->philo_count];
	program->philos[i].program = program;
	pthread_mutex_init(&program->philos[i].mutex, NULL);
}

static void	init_philos(t_program *program)
{
	int	i;

	i = 0;
	while (i < program->philo_count)
	{
		init_one_philo(program, i);
		i++;
	}
}

void	data_init(t_program *program)
{
	program->stop = false;
	program->philos = malloc(sizeof(t_philo) * program->philo_count);
	if (!program->philos)
		error_exit("malloc fail");
	program->forks = malloc(sizeof(t_fork) * program->philo_count);
	if (!program->forks)
	{
		free(program->philos);
		error_exit("malloc fail");
	}
	pthread_mutex_init(&program->stop_mutex, NULL);
	pthread_mutex_init(&program->print_mutex, NULL);
	init_forks(program);
	init_philos(program);
}