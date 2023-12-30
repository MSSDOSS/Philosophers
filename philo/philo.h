/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-haia <hel-haia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 13:31:22 by hel-haia          #+#    #+#             */
/*   Updated: 2023/12/30 01:20:04 by hel-haia         ###   ########.fr       */
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
	int				nums_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				n_eats;
	int				is_alive;
	pthread_mutex_t	*death;
	pthread_mutex_t	*to_print;

}	t_args;

typedef struct s_init_philo
{
	int					id;
	int					start_meal;
	long long			last_meal;
	long long			time;
	t_args				*args;
	pthread_t			t;
	pthread_mutex_t		*right_fork;
	pthread_mutex_t		*left_fork;
}	t_init_philo;

int				error_exiter(char *str);
void			ft_my_usleep(long long n);
int				all_parse(int ac, char **av);
int				ft_atoi(const char *str);
int				ft_strlen(char *str);
int				check_is_numiric(char **av);
int				bad_arguments(int ac, char **av);
t_args			*initialise(char **av, t_args *args);
void			init_forks(t_init_philo	*p, pthread_mutex_t	*forks);
t_init_philo	*func(char	**av);
long long		get_time(void);
#endif