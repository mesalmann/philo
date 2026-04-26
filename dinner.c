#include "philo.h"

static void eat(t_philo *philo)
{
    pthread_mutex_lock(&philo->left_fork->fork);
    write_status(philo, "has taken a fork");
    pthread_mutex_lock(&philo->right_fork->fork);
    write_status(philo, "has taken a fork");

    write_status(philo, "is eating");
    set_long(&philo->philo_mtx, &philo->last_meal_time, get_time_ms());
    
    // Yemek sayacını güvenli bir şekilde artır
    pthread_mutex_lock(&philo->philo_mtx);
    philo->meals_counter++;
    if (philo->table->nbr_limit_meals > 0 && philo->meals_counter == philo->table->nbr_limit_meals)
        philo->full = true;
    pthread_mutex_unlock(&philo->philo_mtx);

    ft_usleep(philo->table->time_to_eat, philo->table);
    
    pthread_mutex_unlock(&philo->left_fork->fork);
    pthread_mutex_unlock(&philo->right_fork->fork);
}

static void monitor_routine(t_table *table)
{
    int i;
    bool all_full;

    while (1)
    {
        i = 0;
        all_full = true;
        while (i < table->philo_nbr)
        {
            if (!get_bool(&table->philos[i].philo_mtx, &table->philos[i].full))
                all_full = false;

            if (get_time_ms() - get_long(&table->philos[i].philo_mtx, &table->philos[i].last_meal_time) >= table->time_to_die)
            {
                set_bool(&table->table_mtx, &table->end_simulation, true);
                pthread_mutex_lock(&table->write_mtx);
                printf("%ld %d died\n",
                    get_time_ms() - table->start_simulation,
                    table->philos[i].id);
                pthread_mutex_unlock(&table->write_mtx);
                return ;
            }
            i++;
        }
        if (all_full && table->nbr_limit_meals > 0)
        {
            set_bool(&table->table_mtx, &table->end_simulation, true);
            return ;
        }
        usleep(1000); // CPU'yu yormamak için 1ms uyu
    }
}

void    *dinner_time(void *arg)
{
    t_philo *philo = (t_philo *)arg;

    // Eğer tek bir filozof varsa, sadece bir çatal vardır (kilitlenme önlemi)
    if (philo->table->philo_nbr == 1)
    {
        write_status(philo, "has taken a fork");
        ft_usleep(philo->table->time_to_die, philo->table);
        return (NULL);
    }

    // Deadlock önlemek için zarif dokunuş: çift olanlar biraz bekler
    if (philo->id % 2 == 0)
        ft_usleep(1, philo->table);

    while (!get_bool(&philo->table->table_mtx, &philo->table->end_simulation))
    {
        eat(philo);
        
        if (get_bool(&philo->philo_mtx, &philo->full))
            break;

        write_status(philo, "is sleeping");
        ft_usleep(philo->table->time_to_sleep, philo->table);
        
        write_status(philo, "is thinking");
    }
    return (NULL);
}




void    dinner_start(t_table *table)
{
    int    nbr;
    int    i;

    i = 0;
    nbr = table->philo_nbr;
    table->start_simulation = get_time_ms();

    while(i < nbr)
    {
        table->philos[i].last_meal_time = get_time_ms();
        pthread_create(&table->philos[i].thread_id, NULL, dinner_time, &table->philos[i]);
        i++;
    }
    
    // Main thread boşa çıktı, onu monitor olarak kullanıyoruz!
    monitor_routine(table);
}