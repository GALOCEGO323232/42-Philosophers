/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgagliar <kgagliar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 17:12:37 by kgagliar          #+#    #+#             */
/*   Updated: 2025/12/07 17:12:37 by kgagliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_fork_mutexes(t_rules *rules)
{
	int	i;

	i = 0;
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
	return (0);
}

static int	init_other_mutexes(t_rules *rules)
{
	int	i;

	i = rules->philo - 1;
	if (pthread_mutex_init(&rules->meal_mutex, NULL) != 0)
	{
		while (i >= 0)
			pthread_mutex_destroy(&rules->forks[i--]);
		return (1);
	}
	if (pthread_mutex_init(&rules->print_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&rules->meal_mutex);
		while (i >= 0)
			pthread_mutex_destroy(&rules->forks[i--]);
		return (1);
	}
	if (pthread_mutex_init(&rules->death_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&rules->print_mutex);
		pthread_mutex_destroy(&rules->meal_mutex);
		while (i >= 0)
			pthread_mutex_destroy(&rules->forks[i--]);
		return (1);
	}
	return (0);
}

int	init_all_mutexes(int i, t_rules *rules)
{
	(void)i;
	if (init_fork_mutexes(rules))
		return (1);
	if (init_other_mutexes(rules))
		return (1);
	return (0);
}

void	destroy_all_mutexes(int i, t_rules *rules)
{
	while (i < rules->philo)
	{
		pthread_mutex_destroy(&rules->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&rules->meal_mutex);
	pthread_mutex_destroy(&rules->print_mutex);
	pthread_mutex_destroy(&rules->death_mutex);
}

int	thread_failure(t_philo *philos, int threads_created)
{
	int	i;

	i = 0;
	while (i < threads_created)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
	free(philos);
	return (1);
}
