/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-haia <hel-haia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 13:31:40 by hel-haia          #+#    #+#             */
/*   Updated: 2023/12/27 12:40:47 by hel-haia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	error_exiter(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		write(1, &str[i++], 1);
	write(1, "\n", 1);
	return (0);
}

// int	ft_atoi(char *str)
// {
// 	int result = 0;

// 	while (*str == ' ' || (*str >= 9 && *str <= 13))
//         	str++;
// 	while (*str >= '0' && *str <= '9')
// 	{
// 		result = result * 10 + *str - '0';
// 		str++;
// 	}
// 	return (result);
// }

static int	overf(long long int pre, long long int cur)
{
	if (cur / 10 == pre)
		return (0);
	return (1);
}

static int	ispace(char *str, int *pi)
{
	int	i;
	int	sign;

	i = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	*pi = i;
	return (sign);
}

int	ft_atoi(const char *str)
{
	int			i;
	int			sign;
	long long	res;
	long long	test;

	res = 0;
	sign = ispace((char *)str, &i);
	while (((char *)str)[i] >= '0' && ((char *)str)[i] <= '9')
	{
		test = res;
		res = res * 10 + (((char *)str)[i] - '0');
		if (overf(test, res) == 1)
		{
			if (sign == -1)
				return (0);
			return (0);
		}
		i++;
	}
	return (res * sign);
}
