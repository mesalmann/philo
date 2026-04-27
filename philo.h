#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>

typedef struct s_program	t_program;
typedef struct s_fork		t_fork;
typedef struct s_philo		t_philo;

struct s_fork
{
	pthread_mutex_t	mutex;
};

struct s_philo
{
	int				id;
	int				eat_count;
	long			last_meal;
	pthread_t		thread;
	pthread_mutex_t	mutex;
	t_fork			*left_fork;
	t_fork			*right_fork;
	t_program		*program;
};

struct s_program
{
	int				philo_count;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				must_eat;
	long			start_time;
	bool			stop;
	t_fork			*forks;
	t_philo			*philos;
	pthread_mutex_t	stop_mutex;
	pthread_mutex_t	print_mutex;
};

void	error_exit(const char *error);

int		is_valid_num(char *s);
int		is_arg_valid(char **av);
int		ft_atoi(char *s);
void	parse_arg(t_program *program, char **av);

void	data_init(t_program *program);
void	clean(t_program *program);

void	start_dinner(t_program *program);
void	*philo_routine(void *arg);

void	log_action(t_philo *philo, char *msg);
void	log_death(t_philo *philo);

int		is_stopped(t_program *program);
void	set_stop(t_program *program);

void	supervisor_loop(t_program *program);

long	get_time_ms(void);
void	ft_usleep(long msec, t_program *program);

#endif