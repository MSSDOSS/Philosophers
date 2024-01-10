/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-haia <hel-haia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 13:31:22 by hel-haia          #+#    #+#             */
/*   Updated: 2024/01/10 16:00:30 by hel-haia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <semaphore.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <sys/ipc.h>
# include <pthread.h>
# include <limits.h>
# include <signal.h>
# include <sys/shm.h>

typedef struct s_args
{
	int				nums_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				is_alive;
	long long		time;
	int				n_eats;
	sem_t			*death;
	sem_t			*print;
	int				done;
}	t_args;

typedef struct s_init_philo
{
	int					n_eat;
	int					id;
	int					start_meal;
	long long			last_meal;
	long long			time;
	t_args				*args;
	pthread_t			t;
	sem_t				*fork;
	sem_t				*finished_eat;
}	t_init_philo;

int				error_exiter(char *str);
void			ft_my_usleep(long long n);
int				all_parse(int ac, char **av);
int				ft_atoi(const char *str);
int				ft_strlen(char *str);
int				check_is_numiric(char **av);
int				bad_arguments(int ac, char **av);
t_args			*initialise(char **av, t_args *args, int ac);
t_init_philo	*func(char	**av, int ac);
long long		get_time(void);
long long		current_time(void);
void			*wait_death(void *p);
void			*wait_eating(void *p);
void			func0(t_init_philo *philo, sem_t *forks, sem_t *print);
void			func1(t_init_philo *philo);
void			n_times(t_init_philo *ph);
// void			init_forks(t_init_philo	*p, pthread_mutex_t	*forks);
// void			*calcultime(void *p);
#endif