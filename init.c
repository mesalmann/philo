#include "philo.h"

static void	init_forks(t_table *t)
{
	int	i;

	i = 0;
	while (i < t->philo_count)
	{
		t->forks[i].id = i + 1;
		pthread_mutex_init(&t->forks[i].mutex, NULL);
		i++;
	}
}

static void	init_philos(t_table *t)
{
	int	i;

	i = 0;
	while (i < t->philo_count)
	{
		t->philos[i].id = i + 1;
		t->philos[i].meals_eaten = 0;
		t->philos[i].last_meal_ms = 0;
		t->philos[i].table = t;
		pthread_mutex_init(&t->philos[i].lock, NULL);
		t->philos[i].left_fork = &t->forks[i];
		t->philos[i].right_fork = &t->forks[(i + 1) % t->philo_count];
		i++;
	}
}

void	init_table(t_table *t)
{
	t->stop_flag = 0;
	t->philos = malloc(sizeof(t_philo) * t->philo_count);
	if (!t->philos)
		exit_error("malloc failed");
	t->forks = malloc(sizeof(t_fork) * t->philo_count);
	if (!t->forks)
	{
		free(t->philos);
		exit_error("malloc failed");
	}
	pthread_mutex_init(&t->print_lock, NULL);
	pthread_mutex_init(&t->stop_lock, NULL);
	init_forks(t);
	init_philos(t);
}

void	launch_sim(t_table *t)
{
	int	i;

	t->start_ms = now_ms();
	i = 0;
	while (i < t->philo_count)
	{
		t->philos[i].last_meal_ms = t->start_ms;
		pthread_create(&t->philos[i].thread, NULL,
			philo_routine, &t->philos[i]);
		i++;
	}
	monitor_table(t);
}

void	cleanup(t_table *t)
{
	int	i;

	i = 0;
	while (i < t->philo_count)
	{
		pthread_join(t->philos[i].thread, NULL);
		pthread_mutex_destroy(&t->philos[i].lock);
		pthread_mutex_destroy(&t->forks[i].mutex);
		i++;
	}
	pthread_mutex_destroy(&t->print_lock);
	pthread_mutex_destroy(&t->stop_lock);
	free(t->forks);
	free(t->philos);
}
