/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouis-j <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 18:33:18 by alouis-j          #+#    #+#             */
/*   Updated: 2022/11/05 16:05:26 by alouis-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	cnt;
	size_t	cnt2;
	char	*big_cpy;
	char	*lil_cpy;

	big_cpy = (char *)big;
	lil_cpy = (char *)little;
	if (!big && !len)
		return (NULL);
	if (!*lil_cpy)
		return (big_cpy);
	cnt = 0;
	while (big_cpy[cnt] && cnt < len)
	{
		cnt2 = 0;
		while (big_cpy[cnt + cnt2] == lil_cpy[cnt2])
		{
			cnt2++;
			if (!lil_cpy[cnt2] && cnt + cnt2 - 1 < len)
				return (big_cpy + cnt);
		}
		cnt++;
	}
	return (NULL);
}
