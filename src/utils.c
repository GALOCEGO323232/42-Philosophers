#include "philo.h"

int	ft_atoi(const char *nprt)
{
	int	i;
	int	result;
	int	signal;

	i = 0;
	result = 0;
	signal = 1;
	while ((nprt[i] >= 9 && nprt[i] <= 13) || nprt[i] == 32)
		i++;
	if (nprt[i] == '-' || nprt[i] == '+')
	{
		if (nprt[i] == '-')
			signal *= -1;
		i++;
	}
	while (nprt[i] >= '0' && nprt[i] <= '9')
	{
		result = result * 10 + (nprt[i] - '0');
		i++;
	}
	return (result * signal);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

size_t	ft_strlen(const char *str)
{
	size_t		len;

	len = 0;
	while (str[len] != '\0')
	{
		len++;
	}
	return (len);
}
