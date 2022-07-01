

#include "../include/philosopher_bonus.h"

static void	*death_checker(void *inp)
{
	t_arg	*arg;
	t_philo	*me;

	me = (t_philo *)inp;
	arg = (t_arg *)me->arg;
	while (arg->stop == 0)
	{
		sem_wait(arg->perm_to_eat);
		if ((int)(timestamp() - me->last_eat) >= arg->time_to_die)
		{
			print_action(arg->writing, "dead\n", arg, me->name);
			arg->stop = 1;
			sem_wait(arg->writing);
			exit(1);
		}
		sem_post(arg->perm_to_eat);
		usleep(500);
		if ((arg->amount_philos != -1) && (me->count_ate >= arg->amount_philos))
			break ;
	}
	return (NULL);
}

static void	philo_sleep(t_arg *arg, int time)
{
	long long int	t;

	t = timestamp();
	while (arg->stop == 0)
	{
		if ((int)(timestamp() - t) >= time)
			break ;
		usleep(100);
	}
}

static void	philo_eat(t_arg *arg, t_philo *me)
{
	if (arg->stop == 0)
	{
		sem_wait(arg->forks);
		print_action(arg->writing, "has taken a fork\n", arg, me->name);
		sem_wait(arg->forks);
		print_action(arg->writing, "has taken a fork\n", arg, me->name);
		sem_wait(arg->perm_to_eat);
		print_action(arg->writing, "is eating\n", arg, me->name);
		me->last_eat = timestamp();
		sem_post(arg->perm_to_eat);
		philo_sleep(arg, arg->time_to_eat);
		sem_post(arg->forks);
		sem_post(arg->forks);
		me->count_ate++;
	}
}

void	philo_life(void *v_philo)
{
	t_arg	*arg;
	t_philo	*me;

	me = (t_philo *)v_philo;
	arg = me->arg;
	me->last_eat = timestamp();
	pthread_create(&me->death_checker, NULL, death_checker, me);
	if (me->name % 2)
		usleep(20000);
	while (arg->stop == 0)
	{
		philo_eat(arg, me);
		if ((arg->amount_philos != -1) && (me->count_ate >= arg->amount_philos))
			break ;
		print_action(arg->writing, "is sleeping\n", arg, me->name);
		philo_sleep(arg, arg->time_to_sleep);
		print_action(arg->writing, "is thinking\n", arg, me->name);
	}
	pthread_join(me->death_checker, NULL);
	exit(0);
}
