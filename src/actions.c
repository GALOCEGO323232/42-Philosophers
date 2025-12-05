#include "philo.h"

void philo_action(t_philo *philo, int actions)
{
    if (actions == 1)
        print_action(philo, "is thinking");
    if (actions == 2)
        print_action(philo, "is eating");
    if (actions == 3)
        print_action(philo, "is sleeping");
    if (actions == 4)
        print_action(philo, "has taken a fork");
    if (actions == 5)
        print_action(philo, "died");
}

static void philo_think(t_philo *philo)
{
    philo_action(philo, 1);
    usleep(500);
    philo_take_forks(philo);
}

static void philo_eat(t_philo *philo)
{
    if (is_someone_dead(philo->rules))
        return;
    philo_action(philo, 2);
    pthread_mutex_lock(&philo->rules->meal_mutex);
    philo->last_meal_time = get_time_ms();
    philo->meals_eaten++;
    pthread_mutex_unlock(&philo->rules->meal_mutex);
    precise_usleep(philo->rules->time_to_eat, philo->rules);
    pthread_mutex_unlock(philo->left_fork);
    pthread_mutex_unlock(philo->right_fork);
}

static void philo_sleep(t_philo *philo)
{
    philo_action(philo, 3);
    precise_usleep(philo->rules->time_to_sleep, philo->rules);
}

void philo_forks_or_eating_or_sleep(t_philo *philo, int action)
{
    if (is_someone_dead(philo->rules))
        return;
    if (action == 1)
        philo_think(philo);
    else if (action == 2)
        philo_eat(philo);
    else if (action == 3)
        philo_sleep(philo);
}
