/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgagliar <kgagliar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 17:12:44 by kgagliar          #+#    #+#             */
/*   Updated: 2025/12/07 17:12:44 by kgagliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	monitor_check_death(t_philo *philos, int i)
{
	t_rules			*rules;
	unsigned long	now;
	unsigned long	time_since_meal;
	unsigned long	last_meal;

	rules = philos[0].rules;
	now = get_time_ms();
	pthread_mutex_lock(&rules->meal_mutex);
	last_meal = philos[i].last_meal_time;
	pthread_mutex_unlock(&rules->meal_mutex);
	time_since_meal = now - last_meal;
	if (time_since_meal > rules->time_to_die)
	{
		pthread_mutex_lock(&rules->death_mutex);
		if (!rules->someone_died)
		{
			rules->someone_died = 1;
			pthread_mutex_lock(&rules->print_mutex);
			printf("%lu %d died\n", now - rules->start_time,
				philos[i].id_philo);
			pthread_mutex_unlock(&rules->print_mutex);
		}
		pthread_mutex_unlock(&rules->death_mutex);
		return (1);
	}
	return (0);
}

static int	check_all_ate(t_philo *philos, t_rules *rules)
{
	int	i;
	int	all_ate;
	int	meals;

	i = 0;
	all_ate = 1;
	while (i < rules->philo)
	{
		pthread_mutex_lock(&rules->meal_mutex);
		meals = philos[i].meals_eaten;
		pthread_mutex_unlock(&rules->meal_mutex);
		if (meals < rules->max_eats)
		{
			all_ate = 0;
			break ;
		}
		i++;
	}
	return (all_ate);
}

static int	monitor_check_meals(t_philo *philos)
{
	t_rules	*rules;
	int		all_ate;

	rules = philos[0].rules;
	if (rules->max_eats <= 0)
		return (0);
	all_ate = check_all_ate(philos, rules);
	if (all_ate)
	{
		pthread_mutex_lock(&rules->death_mutex);
		if (!rules->someone_died)
			rules->someone_died = 1;
		pthread_mutex_unlock(&rules->death_mutex);
		return (1);
	}
	return (0);
}

void	*monitor_routine(void *arg)
{
	t_philo	*philos;
	t_rules	*rules;
	int		i;

	philos = (t_philo *)arg;
	rules = philos[0].rules;
	usleep(1000);
	while (1)
	{
		i = 0;
		while (i < rules->philo)
		{
			if (monitor_check_death(philos, i))
				return (NULL);
			i++;
		}
		if (monitor_check_meals(philos))
			return (NULL);
		usleep(1000);
	}
}
