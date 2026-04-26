#include "philo.h"

static void    *ft_malloc(size_t nbr)
{
    void    *res;

    res = malloc(nbr);
    if (res == NULL)
        error_exit("Error: malloc failed");
    return res;
}

static void    fork_init(t_table *table)
{
    int i;

    i = 0;
    while(i < table->philo_nbr)
    {
        pthread_mutex_init(&table->forks[i].fork, NULL);
        //i. forku mutexle
        table->forks[i].fork_id = i;
        //i.forkun id si idir.
        i++;
    }
}

static void    philo_init(t_table *table)
{
    int i;

    i = 0;
    while (i < table->philo_nbr)
    {
        table->philos[i].id = i + 1;  // 1'den başlar
        table->philos[i].meals_counter = 0; //0 dan başlar
        table->philos[i].full = false; //aç başlar
        table->philos[i].left_fork = &table->forks[i]; //soldaki çatal id si kaçıncı philoysa o numaradır
        table->philos[i].right_fork = &table->forks[(i + 1) % table->philo_nbr];
        //sağdaki çatal örn 1. philo soldaki 0 sağdaki 1
        //5 philo için 5.philonun solundaki 5 sağındaki çatal 0 dır yani
        //çatal sayısı mod philo sayısı
        table->philos[i].table = table;
        pthread_mutex_init(&table->philos[i].philo_mtx, NULL);
        i++;
    }
}


void    data_init(t_table *table)
{
    table->end_simulation = false;
    table->philos = ft_malloc(table->philo_nbr * sizeof(t_philo));
    table->forks = ft_malloc(table->philo_nbr * sizeof(t_fork));
    pthread_mutex_init(&table->table_mtx, NULL);
    pthread_mutex_init(&table->write_mtx, NULL);
    fork_init(table);
    philo_init(table);
}

void clean(t_table *table)
{
    int i;

    // Tüm threadlerin bitmesini bekle
    i = 0;
    while (i < table->philo_nbr)
    {
        pthread_join(table->philos[i].thread_id, NULL);
        i++;
    }
    
    // Mutexleri yok et
    i = 0;
    while (i < table->philo_nbr)
    {
        pthread_mutex_destroy(&table->forks[i].fork);
        pthread_mutex_destroy(&table->philos[i].philo_mtx);
        i++;
    }
    pthread_mutex_destroy(&table->table_mtx);
    pthread_mutex_destroy(&table->write_mtx);
    
    // Hafızayı serbest bırak
    free(table->forks);
    free(table->philos);
}