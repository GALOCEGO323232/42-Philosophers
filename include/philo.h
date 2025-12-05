#ifndef PHILO_H
#define PHILO_H

# define PHILO_MAX 200
# define MIN_TIME 60

#include <pthread.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct s_rules
{
	unsigned long time_to_die;
	unsigned long time_to_eat;
	unsigned long time_to_sleep;
	unsigned long start_time;
	int philo;
	int max_eats;
	int	someone_died;
	pthread_mutex_t *forks;
	pthread_mutex_t print_mutex;
	pthread_mutex_t meal_mutex;
} t_rules;

typedef struct s_philo
{
	int id_philo;
	int meals_eaten;
	unsigned long last_meal_time;
	t_rules *rules;
	pthread_mutex_t *left_fork;
	pthread_mutex_t *right_fork;
	pthread_t thread;
} t_philo;

//-----------------init-------------------

t_rules	*init_rules(int argc, char **argv);
t_philo *init_philo(t_rules *rules);
int		start_threads(t_rules *rules, t_philo *philos)

//-----------------utils------------------

void	*ft_calloc(size_t nmemb, size_t size);
int		ft_atoi(const char *nprt);
int		ft_isdigit(int c);
void	ft_bzero(void *s, size_t n);
size_t	ft_strlen(const char *str);

//----------------free--------------------

t_rules *free_rules(t_rules *rules);

//---------------mutex--------------------

void 	destroy_all_mutexes(int i, t_rules *rules);
int 	init_all_mutexes(int i, t_rules *rules);
int 	thread_failure(t_philo *philos, int threads_created);

//---------------monitor------------------

unsigned long get_time_ms(void);
void		  precise_usleep(long time_in_ms);
void	      *monitor_routine(void *arg);

//---------------actions-------------------

void 	philo_take_forks(t_philo *philo);
void	print_action(t_philo *philo, char *msg);
void	philo_action(t_philo *philo, int actions);
void 	philo_forks_or_eating_or_sleep(t_philo *philo, int actions);
void 	*philo_routine(void *arg);
