#include "philo.h"

static void handle_one_philo(t_philo *philo)
{
    philo_action(philo, 4);
    precise_usleep(philo->rules->time_to_die, philo->rules);
    pthread_mutex_lock(&philo->rules->death_mutex);
    pthread_mutex_lock(&philo->rules->print_mutex);
    printf("%lu %d died\n",
        get_time_ms() - philo->rules->start_time, philo->id_philo);
    philo->rules->someone_died = 1;
    pthread_mutex_unlock(&philo->rules->print_mutex);
    pthread_mutex_unlock(&philo->rules->death_mutex);
}

static void philo_loop(t_philo *philo)
{
	while (!is_someone_dead(philo->rules) && 
		(philo->rules->max_eats == 0 || 
			philo->meals_eaten < philo->rules->max_eats))
	{
		philo_forks_or_eating_or_sleep(philo, 1);
		if (is_someone_dead(philo->rules))
			break ;
		philo_forks_or_eating_or_sleep(philo, 2);
		if (is_someone_dead(philo->rules))
			break ;
		philo_forks_or_eating_or_sleep(philo, 3);
	}
}

void	*philo_routine(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    if (philo->rules->philo == 1)
        return (handle_one_philo(philo), NULL);
    if (philo->id_philo % 2 == 0)
        precise_usleep(1, philo->rules);
    philo_loop(philo);
    return (NULL);
}
