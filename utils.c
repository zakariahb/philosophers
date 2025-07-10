/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zalaksya <zalaksya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 20:51:54 by zalaksya          #+#    #+#             */
/*   Updated: 2025/07/08 17:06:02 by zalaksya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_usleep(long long time, t_data *data)
{
	(void)data;
	long long	start;

	start = get_current_time();
	while ((get_current_time() - start) < time)
	{
		// pthread_mutex_lock(&data->death_mutex);
		// pthread_mutex_lock(&data->meals);
		// if (data->someone_died || data->eating_enough)
		// 	return (pthread_mutex_unlock(&data->meals), pthread_mutex_unlock(&data->death_mutex), 0);
		// pthread_mutex_unlock(&data->death_mutex);
		// pthread_mutex_unlock(&data->meals);
		usleep(500);
	}
	return (0);
}

long long	get_current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

char	**parsing(char **av)
{
	char	*p;
	char	**ar;

	ar = NULL;
	p = ft_check_join(av);
	if (!p)
		return (NULL);
	ar = ft_check_arg(&p);
	free(p);
	if (!ar)
		return (NULL);
	return (ar);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

void	print_message(t_data *data, char *str, int id)
{
	pthread_mutex_lock(&data->print_lock);
	pthread_mutex_lock(&data->death_mutex);
	if (!data->someone_died)
		printf("%lld %d %s\n", get_current_time()
			- data->start_simulation, id, str);
	pthread_mutex_unlock(&data->death_mutex);
	pthread_mutex_unlock(&data->print_lock);
}
