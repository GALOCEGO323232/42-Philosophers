/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgagliar <kgagliar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 17:12:29 by kgagliar          #+#    #+#             */
/*   Updated: 2025/12/07 17:12:29 by kgagliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	handle_one_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	philo_action(philo, 4);
	pthread_mutex_unlock(philo->left_fork);
	precise_usleep(philo->rules->time_to_die, philo->rules);
}

static void	philo_loop(t_philo *philo)
{
	while (!is_someone_dead(philo->rules))
	{
		if (philo->rules->max_eats > 0)
		{
			pthread_mutex_lock(&philo->rules->meal_mutex);
			if (philo->meals_eaten >= philo->rules->max_eats)
			{
				pthread_mutex_unlock(&philo->rules->meal_mutex);
				break ;
			}
			pthread_mutex_unlock(&philo->rules->meal_mutex);
		}
		philo_forks_or_eating_or_sleep(philo, 1);
		if (is_someone_dead(philo->rules))
			break ;
		philo_forks_or_eating_or_sleep(philo, 2);
		if (is_someone_dead(philo->rules))
			break ;
		philo_forks_or_eating_or_sleep(philo, 3);
		if (is_someone_dead(philo->rules))
			break ;
		if (philo->id_philo % 2 == 0)
			usleep(100);
	}
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->rules->philo == 1)
		return (handle_one_philo(philo), NULL);
	if (philo->id_philo % 2 == 0)
		usleep(philo->rules->time_to_eat * 1000);
	philo_loop(philo);
	return (NULL);
}

void	print_action(t_philo *philo, char *msg)
{
	if (philo->rules->someone_died)
		return ;
	pthread_mutex_lock(&philo->rules->print_mutex);
	if (!philo->rules->someone_died)
	{
		printf("%lu %d %s\n",
			get_time_ms() - philo->rules->start_time,
			philo->id_philo, msg);
	}
	pthread_mutex_unlock(&philo->rules->print_mutex);
}
