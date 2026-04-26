#include "philo.h"

void	error_exit(const char *error)
{
	printf("%s\n", error);
	exit(EXIT_FAILURE);
}

void write_status(t_philo *philo, const char *status)
{
	long time;

	pthread_mutex_lock(&philo->table->write_mtx);
	if (!get_bool(&philo->table->table_mtx, &philo->table->end_simulation))
	{
		time = get_time_ms() - philo->table->start_simulation;
		printf("%ld %d %s\n", time, philo->id, status);
	}
	pthread_mutex_unlock(&philo->table->write_mtx);
}
