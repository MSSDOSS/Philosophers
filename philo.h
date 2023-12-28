/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-haia <hel-haia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 13:31:22 by hel-haia          #+#    #+#             */
/*   Updated: 2023/12/27 21:41:54 by hel-haia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdbool.h>

typedef struct s_args
{
	int	nums_of_philos;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	n_eats;
	int	is_alive;
}	t_args;

typedef struct s_init_philo
{
	int					id;
	int					start_meal;
	int					last_meal;
	t_args				*args;
	pthread_t			t;
	pthread_mutex_t		*right_fork;
	pthread_mutex_t		*left_fork;
}	t_init_philo;

int	error_exiter(char *str);
int	all_parse(int ac, char **av);
int	ft_atoi(const char *str);
int	ft_strlen(char *str);
int	check_is_numiric(char **av);
int	bad_arguments(int ac, char **av);

#endif