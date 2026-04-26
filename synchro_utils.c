#include "philo.h"

// Set a boolean value safely
void	set_bool(t_mtx *mtx, bool *dest, bool value)
{
	pthread_mutex_lock(mtx);
	*dest = value;
	pthread_mutex_unlock(mtx);
}

// Get a boolean value safely
bool	get_bool(t_mtx *mtx, bool *value)
{
	bool	ret;

	pthread_mutex_lock(mtx);
	ret = *value;
	pthread_mutex_unlock(mtx);
	return (ret);
}

// Set a long value safely
void	set_long(t_mtx *mtx, long *dest, long value)
{
	pthread_mutex_lock(mtx);
	*dest = value;
	pthread_mutex_unlock(mtx);
}

// Get a long value safely
long	get_long(t_mtx *mtx, long *value)
{
	long	ret;

	pthread_mutex_lock(mtx);
	ret = *value;
	pthread_mutex_unlock(mtx);
	return (ret);
}
