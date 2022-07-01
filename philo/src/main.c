

#include "../include/philosopher.h"

int	dead_mtx(t_p *p)
{
	pthread_mutex_lock(&p->data.dead);
	if (p->data.stop == 1)
	{
		pthread_mutex_unlock(&p->data.dead);
		return (-1);
	}
	pthread_mutex_unlock(&p->data.dead);
	return (1);
}

void	ft_stop(t_p *philo)
{
	int	i;

	i = -1;
	if (!(dead_mtx(philo)))
		ft_usleep(1, philo->ph);
	while (++ i < philo->data.num_philos)
	{
		pthread_join(philo->ph[i].philo_id, NULL);
	}
	pthread_mutex_destroy(&philo->data.write_mutex);
	i = -1;
	while (++ i < philo->data.num_philos)
	{
		pthread_mutex_destroy(&philo->ph[i].left_fork);
	}
}

int	ft_prog(int argc, char *argv[], t_p *philo)
{
	if (!parse(argc, argv))
	{
		error_message(1);
		return (1);
	}
	if (!init_argc(philo, argc, argv))
	{
		error_message(1);
		return (1);
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	t_p	philo;

	if (ft_prog(argc, argv, &philo))
		return (1);
	philo.ph = malloc(sizeof(t_philo) * philo.data.num_philos);
	if (!philo.ph)
	{
		error_message(2);
		return (1);
	}
	if (!(init_mutex(&philo)))
	{
		error_message(4);
		free(philo.ph);
		return (1);
	}
	ft_pthread(&philo);
	ft_stop(&philo);
	free(philo.ph);
	return (0);
}
