

#include "../include/philosopher_bonus.h"

void	print_action(sem_t *writing, char *str, t_arg *arg, int name)
{
	int64_t	time;

	sem_wait(writing);
	time = -1;
	time = timestamp() - arg->f_timestamp;
	if ((arg->stop == 0) && time >= 0 && time <= 2147483647)
	{
		printf("%lld ", time);
		printf("%d %s", name, str);
	}
}

int	ft_check(unsigned long result, int sign)
{
	if (result >= 9223372036854775807 && sign > 0)
		return (-1);
	if (result >= 9223372036854775807 && sign < 0)
		return (0);
	return (1);
}

int	ft_atoi(const char *str)
{
	int				i;
	unsigned long	result;
	int				sign;

	i = 0;
	result = 0;
	sign = 1;
	while (str[i] == '\n' || str[i] == '\f' || str[i] == '\t'
		|| str[i] == '\r' || str[i] == '\v' || str[i] == ' ')
		i ++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -sign;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	if (ft_check(result, sign) != 1)
		return (ft_check(result, sign));
	return (result * sign);
}

long long int	timestamp(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}
