/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_die_thread.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-haia <hel-haia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 22:20:35 by hel-haia          #+#    #+#             */
/*   Updated: 2024/01/10 15:52:02 by hel-haia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	n_eat_loop(t_init_philo *ph, int *i, \
int num_of_philo, int *nums)
{
	if (*i >= num_of_philo)
		*i = 0;
	pthread_mutex_lock(&ph[*i].lastmeal);
	if (ph[*i].n_eat == 0)
	{
		ph[*i].n_eat--;
		*nums = *nums - 1;
	}
	pthread_mutex_unlock(&ph[*i].lastmeal);
	if (*nums == 0)
	{
		pthread_mutex_lock(ph->args->to_print);
		pthread_mutex_unlock(ph->args->death);
	}
	*i = *i + 1;
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
		if (ph->args->n_eats != -1 && id == 1)
			n_eat_loop(ph, &i, num_of_philo, &nums);
		pthread_mutex_lock(&ph->lastmeal);
		if (get_time() - ph->last_meal > ph->args->time_to_die)
		{
			pthread_mutex_lock(ph->args->to_print);
			printf("%lld %d died\n", get_time() - ph->time, ph->id);
			pthread_mutex_unlock(ph->args->death);
		}
		pthread_mutex_unlock(&ph->lastmeal);
		usleep(200);
	}
}
