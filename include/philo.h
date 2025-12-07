/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgagliar <kgagliar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 17:19:04 by kgagliar          #+#    #+#             */
/*   Updated: 2025/12/07 17:19:04 by kgagliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define PHILO_MAX 200
# define MIN_TIME 60

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_rules
{
	unsigned long	time_to_die;
	unsigned long	time_to_eat;
	unsigned long	time_to_sleep;
	unsigned long	start_time;
	int				philo;
	int				max_eats;
	int				someone_died;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	meal_mutex;
	pthread_mutex_t	death_mutex;
}	t_rules;

typedef struct s_philo
{
	int				id_philo;
	int				meals_eaten;
	unsigned long	last_meal_time;
	t_rules			*rules;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_t		thread;
}	t_philo;

t_rules			*init_rules(int argc, char **argv);
t_philo			*init_philo(t_rules *rules);
int				start_threads(t_rules *rules, t_philo *philos);
void			*ft_calloc(size_t nmemb, size_t size);
int				ft_atoi(const char *nprt);
int				ft_isdigit(int c);
void			ft_bzero(void *s, size_t n);
size_t			ft_strlen(const char *str);
t_rules			*free_rules(t_rules *rules);
void			destroy_all_mutexes(int i, t_rules *rules);
int				init_all_mutexes(int i, t_rules *rules);
int				thread_failure(t_philo *philos, int threads_created);
unsigned long	get_time_ms(void);
void			precise_usleep(unsigned long time_in_ms, t_rules *rules);
void			*monitor_routine(void *arg);
void			print_action(t_philo *philo, char *msg);
void			philo_action(t_philo *philo, int actions);
void			philo_forks_or_eating_or_sleep(t_philo *philo, int actions);
void			*philo_routine(void *arg);
void			set_someone_dead(t_rules *rules);
int				is_someone_dead(t_rules *rules);
void			philo_sleep(t_philo *philo);
void			philo_eat(t_philo *philo);
void			philo_think(t_philo *philo);
int				philo_try_take_forks(t_philo *philo);

#endif