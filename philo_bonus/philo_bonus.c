/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-haia <hel-haia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 13:31:36 by hel-haia          #+#    #+#             */
/*   Updated: 2024/01/10 16:07:23 by hel-haia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	loop(t_init_philo *ph)
{
	while (1)
	{
		sem_wait(ph->fork);
		sem_wait(ph->args->print);
		printf("%lld %d has taken a fork\n", \
		get_time() - ph->args->time, ph->id);
		sem_post(ph->args->print);
		sem_wait(ph->fork);
		sem_wait(ph->args->print);
		printf("%lld %d has taken a fork\n", \
		get_time() - ph->args->time, ph->id);
		sem_post(ph->args->print);
		n_times(ph);
		ft_my_usleep(ph->args->time_to_eat);
		sem_post(ph->fork);
		sem_post(ph->fork);
		sem_wait(ph->args->print);
		printf("%lld %d is sleeping\n", get_time() - ph->args->time, ph->id);
		sem_post(ph->args->print);
		ft_my_usleep(ph->args->time_to_sleep);
		sem_wait(ph->args->print);
		printf("%lld %d is thinking\n", get_time() - ph->args->time, ph->id);
		sem_post(ph->args->print);
	}
}

void	*calcultime(void *p)
{
	t_init_philo	*ph;
	int				num_of_philo;
	int				nums;
	int				i;
	int				id;

	ph = (t_init_philo *)p;
	num_of_philo = ph->args->nums_of_philos;
	nums = ph->args->nums_of_philos;
	i = 0;
	id = ph->id;
	while (1)
	{
		if (get_time() - ph->last_meal > ph->args->time_to_die)
		{
			sem_wait(ph->args->print);
			printf("%lld %d died\n", get_time() - ph->args->time, ph->id);
			sem_post(ph->args->death);
		}
	}
}

void	*routine(t_init_philo *ph)
{
	pthread_t	t1;

	ph->last_meal = get_time();
	if (pthread_create(&t1, NULL, &calcultime, ph) != 0)
		return (NULL);
	if (ph->id % 2)
		usleep(500);
	loop(ph);
	return (NULL);
}

void	init_forks(t_init_philo *philo)
{
	int		k;
	int		j;
	sem_t	*print;
	sem_t	*forks;

	j = 0;
	k = philo->args->nums_of_philos;
	print = malloc(sizeof(sem_t) * k);
	if (!print)
		return ;
	forks = malloc (sizeof(sem_t) * philo->args->nums_of_philos);
	if (!forks)
		exit (1);
	sem_unlink("forks");
	sem_unlink("print");
	forks = sem_open("forks", O_CREAT, 0644, k);
	print = sem_open("print", O_CREAT, 0644, 1);
	if (forks == SEM_FAILED || print == SEM_FAILED)
		exit (1);
	if (philo->args->n_eats != -1)
		func1(philo);
	func0(philo, forks, print);
}

int	main(int ac, char **av)
{
	t_init_philo	*p;

	if (ac == 5 || ac == 6)
	{
		if (all_parse(ac, av) == 0)
			return (-1);
	}
	else
		return (error_exiter("Error: invalid arguments amount!!"), -1);
	p = func(av + 1, ac);
	if (!p)
		return (-1);
	init_forks(p);
	fork_p(p);
	return (0);
}
