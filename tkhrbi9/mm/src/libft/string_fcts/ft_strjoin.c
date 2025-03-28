/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouis-j <alouis-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 22:33:31 by alouis-j          #+#    #+#             */
/*   Updated: 2022/11/05 16:04:33 by alouis-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		cnt;

	if (!s1)
		return ((char *)s2);
	if (!s2)
		return ((char *)s1);
	str = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!str)
		return (NULL);
	cnt = -1;
	while (s1[++cnt])
		str[cnt] = s1[cnt];
	cnt = -1;
	while (s2[++cnt])
		str[ft_strlen(s1) + cnt] = s2[cnt];
	str[ft_strlen(s1) + cnt] = 0;
	return (str);
}
