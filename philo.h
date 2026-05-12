/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesalman <mesalman@student.42istanbul.com  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 13:32:12 by mesalman          #+#    #+#             */
/*   Updated: 2026/05/05 13:32:13 by mesalman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	int				meal_count;
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
	long			starvation_ms;
	long			meal_ms;
	long			nap_ms;
	int				max_meals;
	long			start_ms;
	int				stop_flag;
	t_fork			*forks;
	pthread_mutex_t	write_lock;
	t_philo			*philos;
}	t_table;

int		read_args(t_table *t, char **av);

int		init_table(t_table *t);
void	launch_sim(t_table *t);
void	cleanup(t_table *t);

void	*philo_life(void *arg);

void	monitor(t_table *t);
int		is_full(t_philo *p);

long	ms_now(void);
void	sleep_ms(long ms, t_table *t);
void	print_state(t_philo *p, char *msg);
void	print_death(t_philo *p);
int		sim_over(t_table *t);

#endif
