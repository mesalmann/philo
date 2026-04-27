#include "philo.h"

int	is_stopped(t_program *program)
{
	int	stop;

	pthread_mutex_lock(&program->stop_mutex);
	stop = program->stop;
	pthread_mutex_unlock(&program->stop_mutex);
	return (stop);
}

void	set_stop(t_program *program)
{
	pthread_mutex_lock(&program->stop_mutex);
	program->stop = true;
	pthread_mutex_unlock(&program->stop_mutex);
}