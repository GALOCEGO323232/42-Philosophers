#include "philo.h"

void	philo_action(t_philo *philo, int actions)
{
	if (actions == 1)
		print_action(philo, "is thinking");
	else if (actions == 2)
		print_action(philo, "is eating");
	else if (actions == 3)
		print_action(philo, "is sleeping");
	else if (actions == 4)
		print_action(philo, "has taken a fork");
	else if (actions == 5)
		print_action(philo, "died");
}

static void	philo_think(t_philo *philo)
{
	philo_action(philo, 1);
	usleep(500);
}

static int	philo_try_take_forks(t_philo *philo)
{
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;

	if (philo->left_fork < philo->right_fork)
	{
		first = philo->left_fork;
		second = philo->right_fork;
	}
	else
	{
		first = philo->right_fork;
		second = philo->left_fork;
	}
	
	pthread_mutex_lock(first);
	philo_action(philo, 4);
	
	if (is_someone_dead(philo->rules))
	{
		pthread_mutex_unlock(first);
		return (0);
	}
	
	pthread_mutex_lock(second);
	
	if (is_someone_dead(philo->rules))
	{
		pthread_mutex_unlock(second);
		pthread_mutex_unlock(first);
		return (0);
	}
	
	philo_action(philo, 4);
	return (1);
}

static void	philo_eat(t_philo *philo)
{
	if (is_someone_dead(philo->rules))
		return;
	
	// Tenta pegar garfos - retorna 0 se falhar
	if (!philo_try_take_forks(philo))
		return;
	
	// Aqui temos certeza que temos ambos os garfos
	philo_action(philo, 2);
	
	pthread_mutex_lock(&philo->rules->meal_mutex);
	philo->last_meal_time = get_time_ms();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->rules->meal_mutex);
	
	precise_usleep(philo->rules->time_to_eat, philo->rules);
	
	// Agora podemos liberar com segurança
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

static void	philo_sleep(t_philo *philo)
{
	philo_action(philo, 3);
	precise_usleep(philo->rules->time_to_sleep, philo->rules);
}

void	philo_forks_or_eating_or_sleep(t_philo *philo, int action)
{
	if (is_someone_dead(philo->rules))
		return;
	if (action == 1)
		philo_think(philo);
	else if (action == 2)
		philo_eat(philo);
	else if (action == 3)
		philo_sleep(philo);
}
