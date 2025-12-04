#include "philo.h"

t_rules	*init_rules(int argc, char **argv)
{
	t_rules *rules;

	rules = malloc(sizeof(t_rules));
	if (!rules)
		return (NULL);
	rules->philo = ft_atoi(argv[1]);
	rules->time_to_die = ft_atoi(argv[2]);
	rules->time_to_eat = ft_atoi(argv[3]);
	rules->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		rules->max_eats = ft_atoi(argv[5]);
	else
		rules->max_eats = 0;
	rules->someone_died = 0;
	rules->forks = malloc(sizeof(pthread_mutex_t) * rules->philo);
	if (!rules->forks)
		return (free_rules(rules));
	if (init_all_mutexes(0, rules))
		return (free_rules(rules));
	return (rules);
}

t_philo *init_philo(t_rules *rules)
{
	t_philo *philosophers;
	int i;

	i = 0;
	philosophers = malloc(sizeof(t_philo) * rules->philo);
	if (!philosophers)
		return (NULL);
	while(i < rules->philo)
	{
		philosophers[i].id_philo = i + 1;
		philosophers[i].meals_eaten = 0;
		philosophers[i].last_meal_time = get_time_ms();
		philosophers[i].rules = rules;
		philosophers[i].left_fork = &rules->forks[i];
		philosophers[i].right_fork = &rules->forks[(i + 1) % rules->philo];
		i++;
	}
	return (philosophers);
}

int	start_threads(t_rules *rules, t_philo *philos)
{
	int 	i;
	int		threads;

	i = 0;
	threads = 0;
	rules->start_time = get_time_ms();
	while (i < rules->philo)
	{
		philos[i].last_meal_time = rules->start_time;
		i++;
	}
	i = 0;
	while (i < rules->philo)
	{
		if (pthread_create(&philos[i].thread, NULL, philo_routine, &philos[i]) != 0)
			break;
		threads++;
		i++;
		usleep(100);
	}
	if (threads != rules->philo)
		return(thread_failure(philos, threads));
	return (0);
}
