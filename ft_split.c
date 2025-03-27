/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zalaksya <zalaksya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 16:28:35 by zalaksya          #+#    #+#             */
/*   Updated: 2025/03/23 14:45:48 by zalaksya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_free(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

size_t	ft_strlenword(char *s, char c)
{
	size_t	len;
	int		i;

	len = 0;
	i = 0;
	while (s[i] != c && s[i] != '\0')
	{
		len++;
		i++;
	}
	return (len);
}

int	count_word(char const *str, char c)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	while (str[i])
	{
		if (str[i] == c)
			k = 0;
		else if (k == 0)
		{
			k = 1;
			j++;
		}
		i++;
	}
	return (j);
}

char	*ft_strndup(char const *str, size_t len)
{
	size_t	i;
	char	*p;

	i = 0;
	p = malloc(len + 1);
	if (!p)
		return (NULL);
	while (i < len)
	{
		p[i] = str[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		index;
	char	**p;

	i = 0;
	if (!s)
		return (NULL);
	p = (char **)malloc((count_word(s, c) + 1) * sizeof(char *));
	if (!p)
		return (NULL);
	index = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (!s[i])
			break ;
		p[index] = ft_strndup(&s[i], ft_strlenword((char *)&s[i], c));
		if (!p[index])
			return (ft_free(p), NULL);
		i += ft_strlenword((char *)&s[i], c);
		index++;
	}
	p[index] = NULL;
	return (p);
}
