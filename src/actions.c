/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgagliar <kgagliar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 17:13:11 by kgagliar          #+#    #+#             */
/*   Updated: 2025/12/07 17:13:11 by kgagliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_think(t_philo *philo)
{
	philo_action(philo, 1);
}

void	philo_eat(t_philo *philo)
{
	if (is_someone_dead(philo->rules))
		return ;
	if (!philo_try_take_forks(philo))
		return ;
	philo_action(philo, 2);
	pthread_mutex_lock(&philo->rules->meal_mutex);
	philo->last_meal_time = get_time_ms();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->rules->meal_mutex);
	precise_usleep(philo->rules->time_to_eat, philo->rules);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	philo_sleep(t_philo *philo)
{
	philo_action(philo, 3);
	precise_usleep(philo->rules->time_to_sleep, philo->rules);
}

static void	define_forks(t_philo *philo, pthread_mutex_t **f,
					pthread_mutex_t **s)
{
	if (philo->left_fork < philo->right_fork)
	{
		*f = philo->left_fork;
		*s = philo->right_fork;
	}
	else
	{
		*f = philo->right_fork;
		*s = philo->left_fork;
	}
}

int	philo_try_take_forks(t_philo *philo)
{
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;

	define_forks(philo, &first, &second);
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
