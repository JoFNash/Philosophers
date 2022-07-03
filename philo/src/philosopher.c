/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olga <olga@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 01:19:22 by olga              #+#    #+#             */
/*   Updated: 2022/07/04 01:19:23 by olga             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

void	other_work(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->write_mutex);
	print_action("is sleeping\n", philo);
	pthread_mutex_unlock(&philo->data->write_mutex);
	ft_usleep(philo->data->time_to_sleep, philo);
	pthread_mutex_lock(&philo->data->write_mutex);
	print_action("is thinking\n", philo);
	pthread_mutex_unlock(&philo->data->write_mutex);
}

void	work_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork);
	pthread_mutex_lock(&philo->data->write_mutex);
	print_action("has taken a fork\n", philo);
	pthread_mutex_unlock(&philo->data->write_mutex);
	if (!philo->right_fork)
	{
		ft_usleep(philo->data->time_to_die * 2, philo);
		return ;
	}
	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(&philo->data->write_mutex);
	print_action("has taken a fork\n", philo);
	pthread_mutex_unlock(&philo->data->write_mutex);
	pthread_mutex_lock(&philo->data->time_eat);
	pthread_mutex_lock(&philo->data->write_mutex);
	print_action("is eating\n", philo);
	philo->nb_eat = time_ph();
	pthread_mutex_unlock(&philo->data->time_eat);
	pthread_mutex_unlock(&philo->data->write_mutex);
	ft_usleep(philo->data->time_to_eat, philo);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(&philo->left_fork);
}

void	*ft_phr(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	if ((philo->philosopher % 2) == 0)
		usleep(600);
	while (philo->data->stop == 0)
	{
		work_philo(philo);
		other_work(philo);
		if (++ philo->kol_eat == philo->data->amount_philos)
		{
			pthread_mutex_lock(&philo->data->finish);
			philo->finish = 1;
			philo->data->finish_p++;
			if (philo->data->finish_p == philo->data->num_philos)
			{
				pthread_mutex_unlock(&philo->data->finish);
				philo->data->stop = 1;
			}
			pthread_mutex_unlock(&philo->data->finish);
			return (NULL);
		}
	}
	return (NULL);
}

int	ft_pthread(t_p *philo)
{
	int	i;

	i = -1;
	while (++i < philo->data.num_philos)
	{
		philo->ph[i].data = &philo->data;
		if (pthread_create(&philo->ph[i].philo_id, NULL, \
			ft_phr, &philo->ph[i]) != 0)
		{
			error_message(5);
			return (1);
		}
		philo->ph[i].nb_eat = time_ph();
		if (philo->ph[i].nb_eat == -1)
			return (1);
	}
	dead_philo(philo, philo->ph);
	return (0);
}
