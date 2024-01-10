/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-haia <hel-haia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 21:32:51 by hel-haia          #+#    #+#             */
/*   Updated: 2024/01/09 21:35:47 by hel-haia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_my_usleep(long long n)
{
	long long	t;

	t = get_time();
	while (get_time() - t < n)
		usleep(100);
}

void	init_forks(t_init_philo	*p, pthread_mutex_t	*forks)
{
	int	i;
	int	num_of_p;

	i = 0;
	num_of_p = p[0].args->nums_of_philos;
	while (i < num_of_p)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
	i = 0;
	while (i < num_of_p)
	{
		p[i].left_fork = &forks[i];
		p[i].right_fork = &forks[(i + 1) % num_of_p];
		i++;
	}
}

t_args	*initialise(char **av, t_args *args, int ac)
{
	args->nums_of_philos = ft_atoi(av[0]);
	args->time_to_die = ft_atoi(av[1]);
	args->time_to_eat = ft_atoi(av[2]);
	args->time_to_sleep = ft_atoi(av[3]);
	if (ac == 6)
		args->n_eats = ft_atoi(av[4]);
	else
		args->n_eats = -1;
	pthread_mutex_init(args->death, NULL);
	pthread_mutex_init(args->to_print, NULL);
	return (args);
}

void	ids_init(t_args *arg, t_init_philo *philos)
{
	int	i;

	i = 0;
	while (i < arg->nums_of_philos)
	{
		pthread_mutex_init(&philos[i].lastmeal, NULL);
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
	arg->death = malloc(sizeof(pthread_mutex_t));
	if (!arg->death)
		return (NULL);
	arg->to_print = malloc(sizeof(pthread_mutex_t));
	if (!arg->to_print)
		return (NULL);
	arg = initialise(av, arg, ac);
	ids_init(arg, philos);
	free(arg);
	return (philos);
}
