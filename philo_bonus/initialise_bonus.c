/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-haia <hel-haia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 21:32:51 by hel-haia          #+#    #+#             */
/*   Updated: 2024/01/10 15:48:28 by hel-haia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	n_times(t_init_philo *ph)
{
	ph->last_meal = get_time();
	sem_wait(ph->args->print);
	printf("%lld %d is eating\n", get_time() - ph->args->time, ph->id);
	sem_post(ph->args->print);
	if (ph->args->n_eats != -1)
	{
		ph->n_eat--;
		if (ph->n_eat == 0)
		{
			sem_post(ph->fork);
			sem_post(ph->fork);
			sem_post(ph->finished_eat);
			exit (0);
		}
	}
}

void	ft_my_usleep(long long n)
{
	long long	t;

	t = get_time();
	while (get_time() - t < n)
		usleep(100);
}

t_args	*initialise(char **av, t_args *args, int ac)
{
	args->nums_of_philos = ft_atoi(av[0]);
	args->time_to_die = ft_atoi(av[1]);
	args->time_to_eat = ft_atoi(av[2]);
	args->time_to_sleep = ft_atoi(av[3]);
	args->time = get_time();
	if (ac == 6)
		args->n_eats = ft_atoi(av[4]);
	else
		args->n_eats = -1;
	return (args);
}

void	ids_init(t_args *arg, t_init_philo *philos)
{
	int		i;

	i = 0;
	sem_unlink("death");
	arg->death = malloc(sizeof(sem_t));
	if (!arg->death)
		return ;
	arg->death = sem_open("death", O_CREAT, 0644, 1);
	while (i < arg->nums_of_philos)
	{
		philos[i].id = i + 1;
		philos[i].n_eat = arg->n_eats;
		philos[i].args = arg;
		i++;
	}
}

t_init_philo	*func(char	**av, int ac)
{
	t_args			*arg;
	t_init_philo	*philos;

	philos = malloc(sizeof(t_init_philo) * ft_atoi(av[0]));
	if (!philos)
		return (NULL);
	arg = malloc(sizeof(t_args));
	if (!arg)
		return (NULL);
	arg = initialise(av, arg, ac);
	ids_init(arg, philos);
	return (philos);
}
