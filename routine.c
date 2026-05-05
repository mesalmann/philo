#include "philo.h"

static void	take_forks(t_philo *p)
{
	t_fork	*first;
	t_fork	*second;

	if (p->left_fork->id < p->right_fork->id)
	{
		first = p->left_fork;
		second = p->right_fork;
	}
	else
	{
		first = p->right_fork;
		second = p->left_fork;
	}
	pthread_mutex_lock(&first->mutex);
	log_state(p, "has taken a fork");
	pthread_mutex_lock(&second->mutex);
	log_state(p, "has taken a fork");
}

static void	eat(t_philo *p)
{
	take_forks(p);
	pthread_mutex_lock(&p->lock);
	p->last_meal_ms = now_ms();
	p->meals_eaten++;
	pthread_mutex_unlock(&p->lock);
	log_state(p, "is eating");
	wait_ms(p->table->time_to_eat, p->table);
	pthread_mutex_unlock(&p->left_fork->mutex);
	pthread_mutex_unlock(&p->right_fork->mutex);
}

static void	handle_solo(t_philo *p)
{
	pthread_mutex_lock(&p->left_fork->mutex);
	log_state(p, "has taken a fork");
	wait_ms(p->table->time_to_die + 1, p->table);
	pthread_mutex_unlock(&p->left_fork->mutex);
}

static void	do_cycle(t_philo *p)
{
	eat(p);
	if (is_full(p))
		return ;
	log_state(p, "is sleeping");
	wait_ms(p->table->time_to_sleep, p->table);
	if (is_stopped(p->table))
		return ;
	log_state(p, "is thinking");
	if (p->table->philo_count % 2 == 1)
		wait_ms(p->table->time_to_eat, p->table);
}

void	*philo_routine(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	if (p->table->philo_count == 1)
	{
		handle_solo(p);
		return (NULL);
	}
	if (p->id % 2 == 0 || (p->table->philo_count % 2 == 1
			&& p->id == p->table->philo_count))
		wait_ms(p->table->time_to_eat, p->table);
	while (!is_stopped(p->table) && !is_full(p))
		do_cycle(p);
	return (NULL);
}
