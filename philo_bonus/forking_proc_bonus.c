/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forking_proc_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-haia <hel-haia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 16:06:05 by hel-haia          #+#    #+#             */
/*   Updated: 2024/01/10 16:08:19 by hel-haia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	func_wait(t_init_philo *philo)
{
	pthread_t	t1;
	pthread_t	t2;
	int			i;

	i = 0;
	philo->args->done = 1;
	if (pthread_create(&t1, NULL, &wait_eating, philo) != 0)
		exit (1);
	if (pthread_create(&t1, NULL, &wait_death, philo) != 0)
		exit (1);
	while (philo->args->done)
		usleep(1000);
	exit (0);
}

void	fork_rest(t_init_philo *philo, pid_t *pid)
{
	int	i;

	i = 0;
	sem_wait(philo->args->death);
	if (philo->args->n_eats != -1)
		func_wait(philo);
	else
		sem_wait(philo->args->death);
	while (i < philo->args->nums_of_philos)
		kill(pid[i++], SIGTERM);
	free(pid);
}

void	fork_p(t_init_philo *philo)
{
	int			i;
	pid_t		*pid;
	long long	l;

	i = 0;
	pid = malloc(sizeof(pid_t) * philo->args->nums_of_philos);
	if (!pid)
		exit (1);
	philo->args->time = get_time();
	l = philo->args->time;
	while (i < philo->args->nums_of_philos)
	{
		pid[i] = fork();
		if (pid[i] == 0)
		{
			routine(&philo[i]);
			exit(0);
		}
		i++;
	}
	fork_rest(philo, pid);
}
