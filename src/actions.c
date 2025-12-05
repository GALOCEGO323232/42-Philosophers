#include "philo.h"

void print_action(t_philo *philo, char *msg)
{
    pthread_mutex_lock(&philo->rules->print_mutex);

    if (philo->rules->someone_died == 0)
        printf("%lu %d %s\n",
            get_time_ms() - philo->rules->start_time,
            philo->id_philo, msg);

    pthread_mutex_unlock(&philo->rules->print_mutex);
}


void	philo_action(t_philo *philo, int actions)
{
	if (actions == 1)
		print_action(philo, "is thinking");
	if (actions == 2)
		print_action(philo, "is eating");
	if (actions == 3)
		print_action(philo, "is sleeping");
	if (actions == 4)
		print_action(philo, "has taken a fork");
	if (actions == 5)
		print_action(philo, "died");	
}

void philo_forks_or_eating_or_sleep(t_philo *philo, int action)
{
	if (is_someone_dead(philo->rules))
		return ;
	if (action == 1)
	{
		philo_action(philo, 1);
		philo_take_forks(philo);
	}
	else if (action == 2)
	{
		philo_action(philo, 2);
		pthread_mutex_lock(&philo->rules->meal_mutex);
		philo->last_meal_time = get_time_ms();
		philo->meals_eaten++;
		pthread_mutex_unlock(&philo->rules->meal_mutex);
		precise_usleep(philo->rules->time_to_eat, philo->rules);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
	else if (action == 3)
	{
		philo_action(philo, 3);
		precise_usleep(philo->rules->time_to_sleep, philo->rules);
	}
}

static void choose_fork_order(t_philo *philo, pthread_mutex_t **first,
                              pthread_mutex_t **second)
{
    if (philo->id_philo % 2 == 0)
    {
        *first = philo->right_fork;
        *second = philo->left_fork;
    }
    else
    {
        *first = philo->left_fork;
        *second = philo->right_fork;
    }
}

void philo_take_forks(t_philo *philo)
{
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;

	choose_fork_order(philo, &first, &second);
	if (is_someone_dead(philo->rules))
		return ;
	pthread_mutex_lock(first);
	if (is_someone_dead(philo->rules))
	{
		pthread_mutex_unlock(first);
		return ;
	}
	philo_action(philo, 4);
	pthread_mutex_lock(second);
	if (is_someone_dead(philo->rules))
	{
		pthread_mutex_unlock(first);
		pthread_mutex_unlock(second);
		return ;
	}
	philo_action(philo, 4);
}
