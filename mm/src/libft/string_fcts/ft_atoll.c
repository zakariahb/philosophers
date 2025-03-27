/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouis-j <alouis-j@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 13:03:00 by alouis-j          #+#    #+#             */
/*   Updated: 2023/02/09 10:20:02 by alouis-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include <limits.h>

int64_t	ft_atoll(const char *nptr)
{
	int64_t	nb;
	int		sig;

	sig = 1;
	nb = 0;
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == ' ')
		nptr++;
	if (*nptr == '+' || *nptr == '-')
	{
		if (*nptr == '-')
			sig *= -1;
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		nb = nb * 10 + (*nptr++ - '0') * sig;
		if (nb > LONG_MAX)
			return (-1);
		else if (nb < LONG_MIN)
			return (0);
	}
	return (nb);
}
