#include "philo.h"

unsigned long get_time_ms(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void precise_usleep(unsigned long time_in_ms, t_rules *rules)
{
    unsigned long start;

    start = get_time_ms();
    while (!is_someone_dead(rules))
    {
        if (get_time_ms() - start >= time_in_ms)
            break;
        usleep(100);
    }
}

static int monitor_check_death(t_philo *philos, int i)
{
    t_rules *rules;
    unsigned long now;
    unsigned long time_since_meal;

    rules = philos[0].rules;
    pthread_mutex_lock(&rules->meal_mutex);
    now = get_time_ms();
    time_since_meal = now - philos[i].last_meal_time;
    pthread_mutex_unlock(&rules->meal_mutex);
    if (time_since_meal > rules->time_to_die)
    {
        pthread_mutex_lock(&rules->death_mutex);
        if (!rules->someone_died)
        {
            pthread_mutex_lock(&rules->print_mutex);
            rules->someone_died = 1;
            printf("%lu %d died\n", now - rules->start_time, philos[i].id_philo);
            pthread_mutex_unlock(&rules->print_mutex);
        }
        pthread_mutex_unlock(&rules->death_mutex);
        return (1);
    }
    return (0);
}

static int monitor_check_meals(t_philo *philos)
{
    int i;
    int all_ate;
    t_rules *rules;

    rules = philos[0].rules;
    if (rules->max_eats <= 0)
        return (0);
    i = 0;
    all_ate = 1;
    while (i < rules->philo)
    {
        pthread_mutex_lock(&rules->meal_mutex);
        if (philos[i].meals_eaten < rules->max_eats)
            all_ate = 0;
        pthread_mutex_unlock(&rules->meal_mutex);
        
        if (!all_ate)
            break;
        i++;
    }
    if (all_ate)
    {
        pthread_mutex_lock(&rules->death_mutex);
        if (!rules->someone_died)
        {
            rules->someone_died = 1;
        }
        pthread_mutex_unlock(&rules->death_mutex);
        return (1);
    }
    return (0);
}

void *monitor_routine(void *arg)
{
    t_philo *philos;
    t_rules *rules;
    int i;

    philos = (t_philo *)arg;
    rules = philos[0].rules;
    usleep(1000);
    while (1)
    {
        i = 0;
        while (i < rules->philo)
        {
            if (monitor_check_death(philos, i))
                return (NULL);
            i++;
        }
        if (monitor_check_meals(philos))
            return (NULL);
        usleep(100);
    }
}
