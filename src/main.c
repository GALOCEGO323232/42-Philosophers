#include "philo.h"

static int	validate_digit_string(char *str)
{
	int	j;

	j = 0;
	if (str[0] == '-')
		return (1);
	if (str[0] == '+')
		j = 1;
	while (str[j])
	{
		if (!ft_isdigit(str[j]))
			return (1);
		j++;
	}
	return (0);
}

static int	validate_limits(int i, long value)
{
	if (i == 1 && (value <= 0 || value > PHILO_MAX))
		return (1);
	if (i >= 2 && i <= 4 && value < MIN_TIME)
		return (1);
	if (i == 5 && value < 0)
		return (1);
	return (0);
}

static int	check_args(int argc, char **argv)
{
	int		i;
	long	value;

	if (argc != 5 && argc != 6)
		return (1);
	i = 1;
	while (i < argc)
	{
		if (validate_digit_string(argv[i]))
			return (1);
		value = ft_atoi(argv[i]);
		if (validate_limits(i, value))
			return (1);
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_rules	*rules;
	t_philo	*philos;

	if (check_args(argc, argv))
		return (write(2, "Error\n", 6), 1);
	rules = init_rules(argc, argv);
	if (!rules)
		return (write(2, "Error\n", 6), 1);
	philos = init_philo(rules);
	if (!philos)
	{
		free_rules(rules);
		return (write(2, "Error\n", 6), 1);
	}
	if (start_threads(rules, philos))
		return (1);
	return (0);
}
