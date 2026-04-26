#include "philo.h"

int ft_atoi(char *s)
{
    int i;
    int res;

    i = 0;
    res = 0;
    
    while(s[i])
    {
        if (res > (INT_MAX - (s[i] - '0')) / 10)
            error_exit("Invalid argument\n");
        res = res * 10 + (s[i] - '0');
        i++;
    }
    return (res);
}

void    parse_arg(t_table *table, char **av)
{
    table->philo_nbr = ft_atoi(av[1]);
    table->time_to_die = ft_atoi(av[2]);
    table->time_to_eat = ft_atoi(av[3]);
    table->time_to_sleep = ft_atoi(av[4]);
    table->nbr_limit_meals = -1;
    if (av[5])
        table->nbr_limit_meals = ft_atoi(av[5]);
}