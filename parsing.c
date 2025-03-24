/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zalaksya <zalaksya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 02:30:23 by zalaksya          #+#    #+#             */
/*   Updated: 2025/03/24 03:12:25 by zalaksya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	is_all_space(char *s)
{
	int	i;

	i = 0;
	while (s && s[i] && (s[i] == ' ' || (s[i] >= 9 && s[i] <= 13)))
		i++;
	return (!s[i]);
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


char **ft_check_arg(char **str)
{
	int		i;
	long	n;
	char	**ar;

	i = 0;
	ar = ft_split(*str, ' ');
	if (!ar)
		return (0);
	while (ar[i])
	{
		n = ft_atoi(ar[i]);
		if (ft_isnum(ar[i]) || check_num(n) || n <= 0)
			return (ft_free(ar), NULL);
		i++;
	}
	if (i != 4 && i != 5)
		return (ft_free(ar), NULL);
	return (ar);
}

char	*ft_check_join(char **av)
{
	int		i;
	char	*temp;
	char	*str;

	i = 1;
	str = NULL;
	temp = NULL;
	while (av[i])
	{
		if (is_all_space(av[i]))
		{
			write(2, "Error\n", 6);
			free(str);
			return (NULL);
		}
		temp = ft_strjoin(str, av[i]);
		free(str);
		str = temp;
		temp = ft_strjoin(str, " ");
		free(str);
		str = temp;
		i++;
	}
	return (str);
}
