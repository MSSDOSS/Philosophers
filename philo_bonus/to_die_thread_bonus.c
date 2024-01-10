/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_die_thread_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-haia <hel-haia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 23:18:33 by hel-haia          #+#    #+#             */
/*   Updated: 2024/01/10 15:38:17 by hel-haia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	func0(t_init_philo *philo, sem_t *forks, sem_t *print)
{
	int	*g;
	int	j;
	int	k;

	j = 0;
	k = philo->args->nums_of_philos;
	while (j < k)
	{
		philo[j].args->print = print;
		philo[j].fork = forks;
		j++;
	}
}

void	func1(t_init_philo *philo)
{
	sem_t	*eat;
	int		k;
	int		j;

	philo->finished_eat = malloc(sizeof(sem_t));
	if (!philo->finished_eat)
		exit (1);
	sem_unlink("eat");
	eat = sem_open("eat", O_CREAT, 0644, philo->args->n_eats);
	k = philo->args->nums_of_philos;
	j = 0;
	while (j < k)
	{
		philo[j].finished_eat = eat;
		j++;
	}
}

void	*wait_eating(void *p)
{
	t_init_philo	*philo;
	int				i;
	int				num_of_philo;

	philo = (t_init_philo *)p;
	i = 0;
	num_of_philo = philo->args->nums_of_philos;
	while (i < num_of_philo)
		sem_wait(philo[i++].finished_eat);
	sem_wait(philo->args->print);
	philo->args->done = 0;
	return (NULL);
}

void	*wait_death(void *p)
{
	t_init_philo	*philo;

	philo = (t_init_philo *)p;
	sem_wait(philo->args->death);
	philo->args->done = 0;
	return (NULL);
}

long long	current_time(void)
{
	static long long	v;
	struct timeval		time;

	gettimeofday (&time, NULL);
	if (v == 0)
		v = (time.tv_sec * 1000) + (time.tv_usec * 0.001);
	return (get_time() - v);
}
