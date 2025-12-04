#include "philo.h"

void *philo_routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	if (philo->id_philo % 2 == 0)
		usleep(100);
	while (philo->rules->someone_died == 0 &&
      (philo->rules->max_eats == 0 || philo->meals_eaten < philo->rules->max_eats))
	{
    philo_action(philo, 1);
    philo_forks_or_eating_or_sleep(philo, 1);
    if (philo->rules->someone_died)
        break ;
    philo_forks_or_eating_or_sleep(philo, 2);
    if (philo->rules->someone_died)
        break ;
    philo_forks_or_eating_or_sleep(philo, 3);
	}
}
