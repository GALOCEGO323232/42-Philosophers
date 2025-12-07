/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgagliar <kgagliar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 17:12:20 by kgagliar          #+#    #+#             */
/*   Updated: 2025/12/07 17:12:20 by kgagliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_philo_start_time(t_rules *rules, t_philo *philos)
{
	int	i;

	rules->start_time = get_time_ms();
	i = 0;
	while (i < rules->philo)
	{
		philos[i].last_meal_time = rules->start_time;
		i++;
	}
}

static int	create_philo_threads(t_rules *rules, t_philo *philos)
{
	int	i;
	int	created;

	i = 0;
	created = 0;
	while (i < rules->philo)
	{
		if (pthread_create(&philos[i].thread, NULL,
				philo_routine, &philos[i]) != 0)
			break ;
		created++;
		i++;
		usleep(100);
	}
	if (created != rules->philo)
		return (thread_failure(philos, created));
	return (0);
}

static void	wait_all_threads(t_rules *rules, t_philo *philos,
		pthread_t monitor)
{
	int	i;

	i = 0;
	while (i < rules->philo)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
	pthread_join(monitor, NULL);
}

int	start_threads(t_rules *rules, t_philo *philos)
{
	pthread_t	monitor;

	init_philo_start_time(rules, philos);
	if (create_philo_threads(rules, philos))
		return (1);
	if (pthread_create(&monitor, NULL, monitor_routine, (void *)philos) != 0)
	{
		set_someone_dead(rules);
		return (thread_failure(philos, rules->philo));
	}
	wait_all_threads(rules, philos, monitor);
	destroy_all_mutexes(0, rules);
	free(philos);
	free_rules(rules);
	return (0);
}
