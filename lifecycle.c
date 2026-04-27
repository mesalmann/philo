#include "philo.h"

void	start_dinner(t_program *program)
{
	int	i;

	i = 0;
	program->start_time = get_time_ms();
	while (i < program->philo_count)
	{
		program->philos[i].last_meal = program->start_time;
		pthread_create(&program->philos[i].thread, NULL,
			philo_routine, &program->philos[i]);
		i++;
	}
	supervisor_loop(program);
}