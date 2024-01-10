/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-haia <hel-haia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 19:02:38 by hel-haia          #+#    #+#             */
/*   Updated: 2024/01/10 15:34:54 by hel-haia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long long	get_time(void)
{
	struct timeval	time;

	gettimeofday (&time, NULL);
	return (((time.tv_sec * 1000) + (time.tv_usec * 0.001)));
}

int	check_is_numiric(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = 0;
		if (av[i][j] == '+')
			j++;
		while (av[i][j])
		{
			if (av[i][j] < '0' || av[i][j] > '9')
			{
				error_exiter("Error: just digits");
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	check_int_max(char **av)
{
	int	i;

	i = 1;
	while (av[i])
	{
		if (ft_strlen(av[i]) > 10 && av[i][0] != '+')
		{
			error_exiter("Error: overflow!!");
			return (0);
		}
		if (ft_atoi(av[i]) < 1)
		{
			error_exiter("Error: invalid number!!");
			return (0);
		}
		i++;
	}
	return (1);
}

int	bad_arguments(int ac, char **av)
{
	if (ac == 6 && ft_atoi(av[5]) <= 0)
	{
		error_exiter \
		("Error: Number of times to eat wrong!!.. should be more than 0");
		return (0);
	}
	if (check_is_numiric(av) == 0)
		return (0);
	if (check_int_max(av) == 0)
		return (0);
	return (1);
}

int	all_parse(int ac, char **av)
{
	if (bad_arguments(ac, av) == 0)
		return (0);
	return (1);
}
