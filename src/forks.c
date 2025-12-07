#include "philo.h"

static void	choose_fork_order(t_philo *philo, pthread_mutex_t **first,
							  pthread_mutex_t **second)
{
	if (philo->left_fork < philo->right_fork)
	{
		*first = philo->left_fork;
		*second = philo->right_fork;
	}
	else
	{
		*first = philo->right_fork;
		*second = philo->left_fork;
	}
}

void	philo_take_forks(t_philo *philo)
{
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;

	choose_fork_order(philo, &first, &second);
	pthread_mutex_lock(first);
	philo_action(philo, 4);
	
	if (is_someone_dead(philo->rules))
	{
		pthread_mutex_unlock(first);
		return;
	}
	pthread_mutex_lock(second);
	if (is_someone_dead(philo->rules))
	{
		pthread_mutex_unlock(second);
		pthread_mutex_unlock(first);
		return;
	}
	philo_action(philo, 4);
}
