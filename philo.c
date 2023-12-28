/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-haia <hel-haia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 13:31:36 by hel-haia          #+#    #+#             */
/*   Updated: 2023/12/28 00:54:11 by hel-haia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void *routine()
// {
// 	printf("test for thread\n");
// 	sleep(3);
// 	printf("ending thread\n");
// 	return 0;
// }

t_init_philo	*func(char** av)
{
	t_args			*arg;
	int				i;
	t_init_philo	*philos;

	philos = malloc(sizeof(t_init_philo) * ft_atoi(av[0]));
	if (!philos)
		exit (1);
	arg = malloc(sizeof(t_args));
	if (!arg)
		exit (1);
	arg->nums_of_philos = ft_atoi(av[0]);
	arg->time_to_die = ft_atoi(av[1]);
	arg->time_to_eat = ft_atoi(av[2]);
	arg->time_to_sleep = ft_atoi(av[3]);
	i = 0;
	while (i < arg->nums_of_philos)
	{
		philos[i].id = i + 1;
		philos[i].args = arg;
		i++;
	}
	return (philos);
}

void	init_forks(t_init_philo	*p, pthread_mutex_t	*forks)
{
	int				i;
	int				num_of_p;
	
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
		p[i].right_fork = &forks[(i + 1)  % num_of_p];
		i++;
	}
}

long long	get_time(void)
{
	struct timeval	time;

	gettimeofday (&time, NULL);
	return (((time.tv_sec * 1000) + (time.tv_usec * 0.001)));
}

void	ft_my_usleep(long long n)
{
	long long	t;

	t = get_time();
	while (get_time() - t < n)
		usleep(100);
}

void*	routine(void*	p)
{
	t_init_philo	*ph;
	long long		time;

	ph = (t_init_philo *)p;
	if (ph->id % 2)
		usleep(500);
	time = get_time();
	while (1)
	{
		pthread_mutex_lock(ph->left_fork);

		printf("%lld ms %d has taken a fork\n",get_time() - time, ph->id);

		pthread_mutex_lock(ph->right_fork);

		printf("%lld ms %d has taken a fork\n",get_time() - time, ph->id);
		printf("%lld ms %d eating\n",get_time() - time, ph->id);

		ft_my_usleep(ph->args->time_to_eat);

		pthread_mutex_unlock(ph->left_fork);
		pthread_mutex_unlock(ph->right_fork);

		printf("%lld ms %d sleeping\n",get_time() - time, ph->id);
		ft_my_usleep(ph->args->time_to_sleep);

		printf("%lld ms %d thinking\n",get_time() - time, ph->id);
	}
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
			exit (1);
		i++;
	}
	while (1)
		;
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
		return (error_exiter("Error: wrong arguments number"));
	p = func(&av[1]);
	forks = malloc(sizeof(pthread_mutex_t) * ft_atoi(av[1]));
	if (!forks)
		exit (1);
	init_forks(p, forks);
	creat_threads(p);
	return (free(forks), 0);
}
