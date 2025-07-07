/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zalaksya <zalaksya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 08:11:30 by zalaksya          #+#    #+#             */
/*   Updated: 2025/07/07 15:52:55 by zalaksya         ###   ########.fr       */
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

static void	ft_eat(t_philo	*philo, t_data	*data)
{
	print_message(data, "is eating", philo->id);
	pthread_mutex_lock(&data->time_last_eat);
	philo->last_meal_time = get_current_time();
	pthread_mutex_unlock(&data->time_last_eat);
	pthread_mutex_lock(&data->meals);
	philo->meals_eaten++;
	pthread_mutex_unlock(&data->meals);
	usleep(data->t_eat * 1000);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
}

static void	ft_sleep(t_philo	*philo, t_data	*data)
{
	print_message(data, "is sleeping", philo->id);
	usleep(data->t_sleep * 1000);
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
		ft_eat(philo, data);
		ft_sleep(philo, data);
		ft_think(philo, data);
	}
	return (NULL);
}
