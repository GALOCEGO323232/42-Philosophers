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
	int philo;
	int max_eats;
	pthread_mutex_t *forks;
	pthread_mutex_t print_mutex;
	int	someone_died;
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


//-----------------utils------------------

void	*ft_calloc(size_t nmemb, size_t size);
int	ft_atoi(const char *nprt);
int	ft_isdigit(int c);
void	ft_bzero(void *s, size_t n);
size_t	ft_strlen(const char *str);

//----------------free--------------------

t_rules *free_rules(t_rules *rules);

//---------------mutex--------------------

int destroy_all_mutexes(int i, t_rules *rules);
int	init_all_mutexes(int i, t_rules *rules);

//---------------monitor------------------

unsigned long get_time_ms(void);