/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olga <olga@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 01:19:45 by olga              #+#    #+#             */
/*   Updated: 2022/07/04 01:19:46 by olga             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher_bonus.h"

static void	init_philo(t_arg *arg)
{
	int		i;
	t_philo	*philo;

	philo = arg->philos;
	i = -1;
	while (++i < arg->num_philos)
	{
		philo[i].name = i + 1;
		philo[i].arg = arg;
		philo[i].count_ate = 0;
	}
}

static void	init_sema(t_arg *arg)
{
	sem_unlink("!forks!");
	sem_unlink("!writing!");
	sem_unlink("!perm!");
	arg->forks = sem_open("!forks!", O_CREAT, 00700, arg->num_philos);
	arg->perm_to_eat = sem_open("!perm!", O_CREAT, 00700, 1);
}

void	init_all(t_arg *arg, char **argv)
{
	arg->num_philos = ft_atoi(argv[1]);
	if (!arg->num_philos || arg->num_philos >= 201 || arg->num_philos <= 0)
		error_message(0);
	arg->time_to_die = ft_atoi(argv[2]);
	if (!arg->time_to_die || arg->time_to_die < 60 || arg->time_to_die <= 0)
		error_message(0);
	arg->time_to_eat = ft_atoi(argv[3]);
	if (!arg->time_to_eat || arg->time_to_eat < 60 || arg->time_to_eat <= 0)
		error_message(0);
	arg->time_to_sleep = ft_atoi(argv[4]);
	if (!arg->time_to_sleep || arg->time_to_sleep < 60 \
		|| arg->time_to_sleep <= 0)
		error_message(0);
	if (argv[5])
		arg->amount_philos = ft_atoi(argv[5]);
	else
		arg->amount_philos = -1;
	if (!arg->amount_philos && arg->amount_philos <= 0)
		error_message(0);
	arg->stop = 0;
	init_sema(arg);
	init_philo(arg);
}

static void	philo_exit(t_arg *arg)
{
	int	i;
	int	ret;

	i = 0;
	while (i < arg->num_philos)
	{
		waitpid(-1, &ret, 0);
		if (ret != 0)
		{
			i = -1;
			while (++i < arg->num_philos)
				kill(arg->philos[i].pid, 15);
			break ;
		}
		i++;
	}
	sem_close(arg->forks);
	sem_close(arg->writing);
	sem_close(arg->perm_to_eat);
	sem_unlink("!forks!");
	sem_unlink("!writing!");
	sem_unlink("!perm!");
}

void	launcher(t_arg *arg)
{
	t_philo	*philos;
	int		i;

	philos = arg->philos;
	i = -1;
	arg->f_timestamp = timestamp();
	while (++i < arg->num_philos)
	{
		philos[i].pid = fork();
		if (philos[i].pid < 0)
			error_message(0);
		if (philos[i].pid == 0)
			philo_life(&philos[i]);
		usleep(200);
	}
	philo_exit(arg);
}
