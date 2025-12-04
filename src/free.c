#include "philo.h"

t_rules *free_rules(t_rules *rules)
{
    if (rules)
    {
        if (rules->forks)
            free(rules->forks);
        free(rules);
    }
    return (NULL);
}
