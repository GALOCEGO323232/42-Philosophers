#include "philo.h"

int init_all_mutexes(int i, t_rules *rules)
{
    while (i < rules->philo)
    {
        if (pthread_mutex_init(&rules->forks[i], NULL) != 0)
        {
            while (--i >= 0)
                pthread_mutex_destroy(&rules->forks[i]);
            return (1);
        }
        i++;
    }
    if (pthread_mutex_init(&rules->meal_mutex, NULL) != 0)
    {
        while (--i >= 0)
            pthread_mutex_destroy(&rules->forks[i]);
        return (1);
    }
    if (pthread_mutex_init(&rules->print_mutex, NULL) != 0)
    {
        pthread_mutex_destroy(&rules->meal_mutex);
        while (--i >= 0)
            pthread_mutex_destroy(&rules->forks[i]);
        return (1);
    }
    return (0);
}

void destroy_all_mutexes(int i, t_rules *rules)
{
	while (i < rules->philo)
	{
		pthread_mutex_destroy(&rules->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&rules->meal_mutex);
	pthread_mutex_destroy(&rules->print_mutex);
}

int thread_failure(t_philo *philos, int threads_created)
{
    int i;
    i = 0;
    while (i < threads_created)
    {
        pthread_join(philos[i].thread, NULL);
        i++;
    }
    free(philos);
    return (1);
}
