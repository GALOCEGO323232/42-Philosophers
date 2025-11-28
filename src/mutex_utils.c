#include "philo.h"

int	init_all_mutexes(int i, t_rules *rules)
{
	while(i < rules->philo)
	{
		pthread_mutex_init(&rules->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&rules->print_mutex, NULL);
	return (0);
}

int destroy_all_mutexes(int i, t_rules *rules)
{
	while (i < rules->philo)
	{
		pthread_mutex_destroy(&rules->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&rules->print_mutex);
}
