#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <pthread.h>
#include <sys/time.h>
#include <limits.h>

typedef pthread_mutex_t t_mtx;
typedef struct s_table t_table;
typedef struct s_fork t_fork;
typedef struct s_philo t_philo;

struct	s_fork
{
	t_mtx	fork;
	int fork_id;
};

struct s_philo
{
	int			id;
	long		meals_counter;
	bool		full;
	long		last_meal_time;
	t_fork		*left_fork;
	t_fork		*right_fork;
	pthread_t	thread_id;
	t_mtx		philo_mtx;
	t_table		*table;
};

struct s_table
{
	long	philo_nbr;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	nbr_limit_meals;
	long	start_simulation;
	bool	end_simulation;
	t_fork	*forks;
	t_philo *philos;
	t_mtx	table_mtx;
	t_mtx	write_mtx;
};


void	error_exit(const char *error);
void    write_status(t_philo *philo, const char *status);
int 	is_arg_valid(char **av);
int 	is_valid_num(char *s);
void    parse_arg(t_table *table, char **av);
int 	ft_atoi(char *s);
void	data_init(t_table *table);
void    clean(t_table *table);
void    dinner_start(t_table *table);

// synchro_utils.c
void	set_bool(t_mtx *mtx, bool *dest, bool value);
bool	get_bool(t_mtx *mtx, bool *value);
void	set_long(t_mtx *mtx, long *dest, long value);
long	get_long(t_mtx *mtx, long *value);

// time_utils.c
long	get_time_ms(void);
void	ft_usleep(long msec, t_table *table);

#endif