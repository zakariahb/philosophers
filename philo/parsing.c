/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zalaksya <zalaksya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 02:30:23 by zalaksya          #+#    #+#             */
/*   Updated: 2025/07/17 17:21:44 by zalaksya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	ft_atoi(const char *str)
{
	long	i;
	long	res;
	long	sign;

	i = 0;
	res = 0;
	sign = 1;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= (-1);
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = (res * 10) + (str[i] - '0');
		if (res > INT_MAX || res < INT_MIN)
			break ;
		i++;
	}
	return (res * sign);
}

static int	ft_isnum(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (str[i] == '\0')
		return (1);
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (1);
		i++;
	}
	return (0);
}

static int	check_num(long n)
{
	if (n >= INT_MIN && n <= INT_MAX)
		return (0);
	return (1);
}

int	parsing(char **str ,t_data *data)
{
	int		i;
	long	n;

	i = 1;
	while (str[i])
	{
		n = ft_atoi(str[i]);
		if (ft_isnum(str[i]) || check_num(n) || n <= 0)
			return (0);
		i++;
	}
	if (!init_data(data, str))
		return (0);
	return (1);
}
