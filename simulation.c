/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zalaksya <zalaksya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 08:11:30 by zalaksya          #+#    #+#             */
/*   Updated: 2025/07/08 16:50:46 by zalaksya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	ft_taking_forks(t_philo	*philo, t_data	*data)
{
	if (philo->id ==  data->n_philo)
	{
		pthread_mutex_lock(philo->r_fork);
		print_message(data, "has right taken fork", philo->id);
		pthread_mutex_lock(philo->l_fork);
		print_message(data, "has left taken fork", philo->id);
	}
	else
	{
		pthread_mutex_lock(philo->l_fork);
		print_message(data, "has left taken fork", philo->id);
		pthread_mutex_lock(philo->r_fork);
		print_message(data, "has right taken fork", philo->id);
	}
}

static void	ft_eat(t_philo	*philo, t_data	*data)
{
	pthread_mutex_lock(&data->eating);
	philo->eating = 1;
	pthread_mutex_unlock(&data->eating);
	
	print_message(data, "is eating", philo->id);
	
	pthread_mutex_lock(&data->time_last_eat);
	philo->last_meal_time = get_current_time();
	pthread_mutex_unlock(&data->time_last_eat);
	ft_usleep(data->t_eat, data);
	
	pthread_mutex_lock(&data->meals);
	philo->meals_eaten++;
	pthread_mutex_unlock(&data->meals);
	
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
	
	pthread_mutex_lock(&data->eating);
	philo->eating = 0;
	pthread_mutex_unlock(&data->eating);
}

static void	ft_sleep(t_philo	*philo, t_data	*data)
{
	print_message(data, "is sleeping", philo->id);
	ft_usleep(data->t_sleep, data);
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
		usleep(50);
	while (!checking_dead(data))
	{
		ft_taking_forks(philo, data);
		ft_eat(philo, data);
		ft_sleep(philo, data);
		ft_think(philo, data);
	}
	return (NULL);
}
