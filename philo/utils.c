/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zalaksya <zalaksya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 20:51:54 by zalaksya          #+#    #+#             */
/*   Updated: 2025/07/17 07:44:17 by zalaksya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_usleep(size_t time, t_data *data)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < time)
	{
		pthread_mutex_lock(&data->death_mutex);
		if (data->someone_died || data->eating_enough)
		{
			pthread_mutex_unlock(&data->death_mutex);
			return (0);
		}
		pthread_mutex_unlock(&data->death_mutex);
		usleep(500);
	}
	return (0);
}

size_t	get_current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	print_message(t_data *data, char *str, int id)
{
	pthread_mutex_lock(&data->print_lock);
	if (!data->someone_died || data->eating_enough)
		printf("%lu %d %s\n", get_current_time()
			- data->start_simulation, id, str);
	pthread_mutex_unlock(&data->print_lock);
}
