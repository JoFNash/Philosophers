/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_bonus.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olga <olga@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 01:19:39 by olga              #+#    #+#             */
/*   Updated: 2022/07/04 01:19:40 by olga             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_BONUS_H
# define PHILOSOPHER_BONUS_H

# include <stdlib.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <semaphore.h>
# include <signal.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>

typedef struct s_philo
{
	int				name;
	pid_t			pid;
	long long int	last_eat;
	int				count_ate;
	struct s_arg	*arg;
	pthread_t		death_checker;
}				t_philo;

typedef struct s_arg
{
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				amount_philos;
	int				stop;
	long long int	f_timestamp;
	sem_t			*forks;
	sem_t			*writing;
	sem_t			*perm_to_eat;
	t_philo			philos[201];
}			t_arg;

long long int	timestamp(void);
void			philo_life(void *v_philo);
void			launcher(t_arg *arg);
void			print_action(sem_t *writing, char *str, t_arg *arg, int name);
void			init_all(t_arg *arg, char **argv);
int				ft_atoi(const char *s);
int				ft_prog(int argc, char *argv[]);
void			error_message(int error);
void			terminate(char *s);

#endif
