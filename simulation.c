/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zalaksya <zalaksya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 08:11:30 by zalaksya          #+#    #+#             */
/*   Updated: 2025/07/01 20:49:20 by zalaksya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	ft_take_fork(t_philo	*philo, t_data	*data)
{
	pthread_mutex_lock(philo->l_fork);
	print_message(data, "has left taken fork", philo->id);
	pthread_mutex_lock(philo->r_fork);
	print_message(data, "has right taken fork", philo->id);
}

static int	ft_eat(t_philo	*philo, t_data	*data)
{
	pthread_mutex_lock(&data->meals);
	philo->eating = 1;
	pthread_mutex_unlock(&data->meals);
	print_message(data, "is eating", philo->id);
	pthread_mutex_lock(&data->time_last_eat);
	philo->last_meal_time = get_current_time();
	if (philo->last_meal_time == 0)
		return (printf("ana Kharj\n"), 0);
	pthread_mutex_unlock(&data->time_last_eat);
	ft_usleep(data->t_eat);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_lock(&data->meals);
	philo->meals_eaten++;
	philo->eating = 0;
	pthread_mutex_unlock(&data->meals);
	return (1);
}

static void	ft_sleep(t_philo	*philo, t_data	*data)
{
	print_message(data, "is sleeping", philo->id);
	ft_usleep(data->t_sleep);
}

static void	ft_think(t_philo	*philo, t_data	*data)
{
	print_message(data, "is thinking", philo->id);
}

void	*start_routine(void *input)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)input;
	data = philo->data;
	if (philo->id % 2 == 0)
		usleep(100);
	while (!checking_dead(philo))
	{
		ft_take_fork(philo, data);
		if (!ft_eat(philo, data))
			return (NULL);
		ft_sleep(philo, data);
		ft_think(philo, data);
	}
	return (NULL);
}
