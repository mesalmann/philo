#include "philo.h"

long	now_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000L + tv.tv_usec / 1000);
}

void	wait_ms(long ms, t_table *t)
{
	long	end_time;

	end_time = now_ms() + ms;
	while (now_ms() < end_time)
	{
		if (is_stopped(t))
			break ;
		usleep(200);
	}
}

void	log_state(t_philo *p, char *msg)
{
	pthread_mutex_lock(&p->table->print_lock);
	if (!is_stopped(p->table))
		printf("%ld %d %s\n",
			now_ms() - p->table->start_ms, p->id, msg);
	pthread_mutex_unlock(&p->table->print_lock);
}

void	log_death(t_philo *p)
{
	pthread_mutex_lock(&p->table->print_lock);
	pthread_mutex_lock(&p->table->stop_lock);
	p->table->stop_flag = 1;
	pthread_mutex_unlock(&p->table->stop_lock);
	printf("%ld %d died\n",
		now_ms() - p->table->start_ms, p->id);
	pthread_mutex_unlock(&p->table->print_lock);
}

int	is_stopped(t_table *t)
{
	int	flag;

	pthread_mutex_lock(&t->stop_lock);
	flag = t->stop_flag;
	pthread_mutex_unlock(&t->stop_lock);
	return (flag);
}
