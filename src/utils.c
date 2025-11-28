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

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t			value;
	void			*ptr;

	if (nmemb == 0 || size == 0)
		return (malloc(0));
	if (nmemb != 0 && size > ((size_t)(-1)) / nmemb)
		return (NULL);
	value = nmemb * size;
	ptr = malloc(value);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, value);
	return (ptr);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*ptr;

	i = 0;
	ptr = (unsigned char *)s;
	while (i < n)
	{
		ptr[i] = 0;
		i++;
	}
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
