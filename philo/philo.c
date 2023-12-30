/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-haia <hel-haia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 13:31:36 by hel-haia          #+#    #+#             */
/*   Updated: 2023/12/30 01:48:04 by hel-haia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*calcultime(void *p)
{
	t_init_philo	*ph;

	ph = (t_init_philo *)p;
	while (1)
	{
		if (get_time() - ph->last_meal > ph->args->time_to_die)
		{
			pthread_mutex_lock(ph->args->to_print);
			printf("%lld ms %d died\n", get_time() - ph->time, ph->id);
			pthread_mutex_unlock(ph->args->death);
		}
		usleep(500);
	}
}

void	loop(t_init_philo *ph)
{
	while (1)
	{
		pthread_mutex_lock(ph->left_fork);
		pthread_mutex_lock(ph->args->to_print);
		printf("%lld ms %d has taken a fork\n", get_time() - ph->time, ph->id);
		pthread_mutex_unlock(ph->args->to_print);
		pthread_mutex_lock(ph->right_fork);
		pthread_mutex_lock(ph->args->to_print);
		printf("%lld ms %d has taken a fork\n", get_time() - ph->time, ph->id);
		pthread_mutex_unlock(ph->args->to_print);
		ph->last_meal = get_time();
		pthread_mutex_lock(ph->args->to_print);
		printf("%lld ms %d eating\n", get_time() - ph->time, ph->id);
		pthread_mutex_unlock(ph->args->to_print);
		ft_my_usleep(ph->args->time_to_eat);
		pthread_mutex_unlock(ph->left_fork);
		pthread_mutex_unlock(ph->right_fork);
		pthread_mutex_lock(ph->args->to_print);
		printf("%lld ms %d sleeping\n", get_time() - ph->time, ph->id);
		pthread_mutex_unlock(ph->args->to_print);
		ft_my_usleep(ph->args->time_to_sleep);
		pthread_mutex_lock(ph->args->to_print);
		printf("%lld ms %d thinking\n", get_time() - ph->time, ph->id);
		pthread_mutex_unlock(ph->args->to_print);
	}
}

void	*routine(void	*p)
{
	t_init_philo	*ph;
	pthread_t		t1;

	ph = (t_init_philo *)p;
	ph->last_meal = get_time();
	if (pthread_create(&t1, NULL, &calcultime, p) != 0)
		exit (1);
	if (ph->id % 2)
		usleep(500);
	ph->time = get_time();
	loop(ph);
	return (0);
}

void	creat_threads(t_init_philo	*p)
{
	int		num_of_p;
	int		i;

	i = 0;
	num_of_p = p[0].args->nums_of_philos;
	while (i < num_of_p)
	{
		if (pthread_create(&p[i].t, NULL, &routine, &p[i]) != 0)
			exit(-1);
		i++;
	}
	pthread_mutex_lock(p[0].args->death);
	pthread_mutex_lock(p[0].args->death);
}

int	main(int ac, char **av)
{
	int				i;
	t_init_philo	*p;
	pthread_mutex_t	*forks;

	i = 1;
	if (ac == 5 || ac == 6)
	{
		if (all_parse(ac, av) == 0)
			exit(1);
	}
	else
		return (error_exiter("Error: invalid arguments amount!!"), 0);
	if (!func(&av[1]))
		exit(1);
	p = func(&av[1]);
	forks = malloc(sizeof(pthread_mutex_t) * ft_atoi(av[1]));
	if (!forks)
		exit(1);
	init_forks(p, forks);
	creat_threads(p);
	return (free(forks), 0);
}
