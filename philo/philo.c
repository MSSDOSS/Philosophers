/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-haia <hel-haia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 13:31:36 by hel-haia          #+#    #+#             */
/*   Updated: 2024/01/02 14:58:59 by hel-haia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*calcultime(void *p)
{
	t_init_philo	*ph;
	int				num_of_philo;
	int				nums;
	int				i;
	int				id;

	ph = (t_init_philo *)p;
	id = ph->id;
	num_of_philo = ph->args->nums_of_philos;
	nums = ph->args->nums_of_philos;
	i = 0;
	while (1)
	{
		if (ph->args->n_eats != -1 && id == 1)
		{
			if (i >= num_of_philo)
				i = 0;
			pthread_mutex_lock(&ph[i].lastmeal);
			if (ph[i].n_eat == 0)
			{
				ph[i].n_eat--;
				nums--;
			}
			pthread_mutex_unlock(&ph[i].lastmeal);
			if (nums == 0)
			{
				pthread_mutex_lock(ph->args->to_print);
				pthread_mutex_unlock(ph->args->death);
			}	
			i++;
		}
		pthread_mutex_lock(&ph->lastmeal);
		if (get_time() - ph->last_meal > ph->args->time_to_die)
		{
			pthread_mutex_lock(ph->args->to_print);
			printf("%lld ms %d died\n", get_time() - ph->time, ph->id);
			pthread_mutex_unlock(ph->args->death);
		}
		pthread_mutex_unlock(&ph->lastmeal);
		usleep(500);
	}
}

// void	nums_eating(t_init_philo *ph)
// {
	// t_args	arg;
	// int		i;

	// i = 0;
	// arg.n_eats = 4;
	// if (arg.n_eats == -1)
	// 	exit(0);
	// while (i < 4)
	// {
	// 	printf("%lld ms %d eating\n", get_time() - ph->time, ph->id);
	// 	i++;
	// }
// }

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

		pthread_mutex_lock(&ph->lastmeal);
		ph->last_meal = get_time();
		pthread_mutex_unlock(&ph->lastmeal);
		pthread_mutex_lock(ph->args->to_print);
		printf("%lld ms %d eating\n", get_time() - ph->time, ph->id);
		pthread_mutex_unlock(ph->args->to_print);

		if (ph->args->n_eats != -1)
		{
			pthread_mutex_lock(&ph->lastmeal);
			ph->n_eat--;
			pthread_mutex_unlock(&ph->lastmeal);
		}
		
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

void	*routine(void *p)
{
	t_init_philo	*ph;
	pthread_t		t1;

	ph = (t_init_philo *)p;
	ph->last_meal = get_time();
	if (pthread_create(&t1, NULL, &calcultime, p) != 0)
		return (NULL);
	if (ph->id % 2)
		usleep(500);
	ph->time = get_time();
	loop(ph);
	return (NULL);
}

int	creat_threads(t_init_philo	*p)
{
	int		num_of_p;
	int		i;

	i = 0;
	num_of_p = p[0].args->nums_of_philos;
	while (i < num_of_p)
	{
		if (pthread_create(&p[i].t, NULL, &routine, &p[i]) != 0)
			return (0);
		i++;
	}
	pthread_mutex_lock(p[0].args->death);
	pthread_mutex_lock(p[0].args->death);
	return (1);
}

int	main(int ac, char **av)
{
	t_init_philo	*p;
	pthread_mutex_t	*forks;

	if (ac == 5 || ac == 6)
	{
		if (all_parse(ac, av) == 0)
			return (-1);
	}
	else
		return (error_exiter("Error: invalid arguments amount!!"), -1);
	if (!func(&av[1], ac))
		return (-1);
	p = func(av+1, ac);
	forks = malloc(sizeof(pthread_mutex_t) * ft_atoi(av[1]));
	if (!forks)
		return (-1);
	init_forks(p, forks);
	if (!creat_threads(p))
		return (-1);
	return (free(forks), 0);
}
