#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>

typedef struct s_table	t_table;

typedef struct s_fork
{
	int				id;
	pthread_mutex_t	mutex;
}	t_fork;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	long			last_meal_ms;
	pthread_t		thread;
	pthread_mutex_t	lock;
	t_fork			*left_fork;
	t_fork			*right_fork;
	t_table			*table;
}	t_philo;

typedef struct s_table
{
	int				philo_count;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				meal_limit;
	long			start_ms;
	int				stop_flag;
	t_fork			*forks;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	stop_lock;
	t_philo			*philos;
}	t_table;

void	exit_error(char *msg);
void	parse_args(t_table *t, char **av);

void	init_table(t_table *t);
void	launch_sim(t_table *t);
void	cleanup(t_table *t);

void	*philo_routine(void *arg);

void	monitor_table(t_table *t);
int		is_full(t_philo *p);

long	now_ms(void);
void	wait_ms(long ms, t_table *t);
void	log_state(t_philo *p, char *msg);
void	log_death(t_philo *p);
int		is_stopped(t_table *t);

#endif
