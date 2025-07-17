/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zalaksya <zalaksya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 20:21:42 by zalaksya          #+#    #+#             */
/*   Updated: 2025/07/17 08:35:34 by zalaksya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	checking_dead(t_data *data)
{
	pthread_mutex_lock(&data->death_mutex);
	if (data->someone_died || data->eating_enough)
		return (pthread_mutex_unlock(&data->death_mutex), 1);
	pthread_mutex_unlock(&data->death_mutex);
	return (0);
}

static int	check_if_eat_full(t_data *data)
{
	int	flag;	
	int	i;

	i = 0;
	flag = 0;
	if (data->t_t_eat > 0)
	{
		while (i < data->n_philo)
		{
			pthread_mutex_lock(&data->meals);
			if (data->philos[i].meals_eaten < data->t_t_eat)
				return (pthread_mutex_unlock(&data->meals), 1);
			pthread_mutex_unlock(&data->meals);
			i++;
		}
		pthread_mutex_lock(&data->meals);
		data->eating_enough = 1;
		return (pthread_mutex_unlock(&data->meals), 0);
	}
	return (1);
}

void	marque_as_died(t_data *data, int id, char *str)
{
	pthread_mutex_lock(&data->death_mutex);
	data->someone_died = 1;
	printf("%lu %d %s\n", get_current_time() - data->start_simulation, id, str);
	pthread_mutex_unlock(&data->death_mutex);
}

static int	check_if_someone_diead(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
	{
		if (!check_one_philo(data, data->philos[i].id))
			return (0);
		pthread_mutex_lock(&data->time_last_eat);
		if (data->philos[i].last_meal_time && get_current_time()
			- data->philos[i].last_meal_time > data->t_die)
		{
			pthread_mutex_unlock(&data->time_last_eat);
			marque_as_died(data, data->philos[i].id, "died");
			return (0);
		}
		pthread_mutex_unlock(&data->time_last_eat);
		i++;
	}
	return (1);
}

int	monitoring(t_data	*data)
{
	while (1)
	{
		if (!check_if_someone_diead(data) || !check_if_eat_full(data))
			return (0);
	}
	return (1);
}
