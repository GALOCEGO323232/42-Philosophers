/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgagliar <kgagliar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 17:12:11 by kgagliar          #+#    #+#             */
/*   Updated: 2025/12/07 17:12:11 by kgagliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	precise_usleep(unsigned long time_in_ms, t_rules *rules)
{
	unsigned long	start;
	unsigned long	elapsed;

	start = get_time_ms();
	while (!is_someone_dead(rules))
	{
		elapsed = get_time_ms() - start;
		if (elapsed >= time_in_ms)
			break ;
		if (time_in_ms - elapsed > 10)
			usleep(5000);
		else if (time_in_ms - elapsed > 1)
			usleep(500);
		else
			usleep(100);
	}
}

int	is_someone_dead(t_rules *rules)
{
	int	val;

	pthread_mutex_lock(&rules->death_mutex);
	val = rules->someone_died;
	pthread_mutex_unlock(&rules->death_mutex);
	return (val);
}

void	set_someone_dead(t_rules *rules)
{
	pthread_mutex_lock(&rules->death_mutex);
	rules->someone_died = 1;
	pthread_mutex_unlock(&rules->death_mutex);
}
