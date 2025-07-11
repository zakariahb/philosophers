/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zalaksya <zalaksya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 16:16:50 by zalaksya          #+#    #+#             */
/*   Updated: 2025/05/27 12:26:23 by zalaksya		###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	create_threads(t_data *data)
{
	int	i;

	i = 0;
	data->start_simulation = get_current_time();
	if (!check_one_philo(data, data->philos[i].id))
		return (0);
	while (i < data->n_philo)
	{
		if (pthread_create(&data->philos[i].thread,
				NULL, start_routine, &data->philos[i]))
		{
			while (--i >= 0)
				pthread_detach(data->philos[i].thread);
			return (1);
		}
		i++;
	}
	monitoring(data);
	i = -1;
	while (++i < data->n_philo)
		pthread_join(data->philos[i].thread, NULL);
	return (0);
}

void	init_data(t_data **data, char **ar)
{
	(*data)->n_philo = ft_atoi(ar[0]);
	(*data)->t_die = ft_atoi(ar[1]);
	(*data)->t_eat = ft_atoi(ar[2]);
	(*data)->t_sleep = ft_atoi(ar[3]);
	if (ar[4])
		(*data)->t_t_eat = ft_atoi(ar[4]);
	else
		(*data)->t_t_eat = -1;
	(*data)->someone_died = 0;
	(*data)->max_meals = 0;
	(*data)->eating_enough = 0;
	ft_free(ar);
}

int	init_mutex(t_data **data)
{
	int	i;

	i = -1;
	(*data)->forks = malloc(sizeof(pthread_mutex_t) * (*data)->n_philo);
	if (!(*data)->forks)
		return (1);
	while (++i < (*data)->n_philo)
	{
		if (pthread_mutex_init(&(*data)->forks[i], NULL))
		{
			while (--i >= 0)
				pthread_mutex_destroy(&(*data)->forks[i]);
			free((*data)->forks);
			return (1);
		}
	}
	if (pthread_mutex_init(&(*data)->time_last_eat, NULL))
		return (1);
	if (pthread_mutex_init(&(*data)->print_lock, NULL))
		return (1);
	if (pthread_mutex_init(&(*data)->meals, NULL))
		return (1);
	if (pthread_mutex_init(&(*data)->death_mutex, NULL))
		return (1);
	return (0);
}

int	init_philos(t_data **data)
{
	int	i;

	i = 0;
	(*data)->philos = malloc((*data)->n_philo * sizeof(t_philo));
	if (!(*data)->philos)
		return (1);
	while (i < (*data)->n_philo)
	{
		(*data)->philos[i].id = i + 1;
		(*data)->philos[i].eating = 0;
		(*data)->philos[i].meals_eaten = 0;
		(*data)->philos[i].last_meal_time = 0;
		(*data)->philos[i].l_fork = &(*data)->forks[i];
		(*data)->philos[i].r_fork = &(*data)->forks[(i + 1) % (*data)->n_philo];
		(*data)->philos[i].data = *data;
		i++;
	}
	return (0);
}

int	ft_init_informatoin(t_data **data, char **ar)
{
	init_data(data, ar);
	if (init_mutex(data))
		return (destroy_mutex(*data), 1);
	if (init_philos(data))
		return (destroy_mutex(*data), 1);
	create_threads(*data);
	destroy_mutex(*data);
	if ((*data)->philos)
		free((*data)->philos);
	if ((*data)->forks)
		free((*data)->forks);
	return (0);
}
