/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dead_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olga <olga@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 01:18:57 by olga              #+#    #+#             */
/*   Updated: 2022/07/04 01:19:00 by olga             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

void	check_dead(t_p *p, t_philo *philo, int i)
{
	if (((time_ph() - p->ph[i].nb_eat) > p->data.time_to_die) \
		|| p->data.num_philos == 1)
	{
		if (p->data.num_philos == 1)
			ft_usleep(p->data.time_to_die, philo);
		pthread_mutex_lock(&philo->data->write_mutex);
		print_action("dead\n", philo);
		pthread_mutex_unlock(&philo->data->write_mutex);
		p->data.stop = 1;
	}
}

void	dead_philo(t_p *p, t_philo *philo)
{
	int	i;

	while (1)
	{
		i = -1;
		usleep(p->data.time_to_die);
		while (p->data.stop == 0 && (++ i < p->data.num_philos))
		{
			pthread_mutex_lock(&philo->data->time_eat);
			check_dead(p, philo, i);
			pthread_mutex_unlock(&philo->data->time_eat);
		}
		if (p->data.stop == 1)
			break ;
	}
}
