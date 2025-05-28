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

void	init_data(t_data **data, char **ar)
{
	(*data)->n_philo = ft_atoi(ar[0]);
	(*data)->t_die = ft_atoi(ar[1]);
	(*data)->t_eat = ft_atoi(ar[2]);
	(*data)->t_sleep = ft_atoi(ar[3]);
}

int	init_mutex(t_data **data)
{
	int	i;

	i = 0;
	(*data)->forks = malloc((*data)->n_philo);
	while (i < (*data)->n_philo)
	{	
		if (pthread_mutex_init(&(*data)->forks[i], NULL) != 0)
			return (1);
		i++;
	}
	pthread_mutex_init(&(*data)->print_lock, NULL);
	return (0);
}

void init_philos(t_data **data)
{
	int	i;
	
	i = 0;
	(*data)->philos = malloc((*data)->n_philo * sizeof(t_philo));
	while (i < (*data)->n_philo)
	{
		(*data)->philos[i].id = i + 1;
		(*data)->philos[i].n_meals = 0;
		(*data)->philos[i].l_fork = &(*data)->forks[(*data)->philos[i].id];
		(*data)->philos[i].r_fork = &(*data)->forks[(*data)->philos[i].id % (*data)->n_philo + 1];
		(*data)->philos[i].data = *data;
		i++;
	}
}

void	ft_init_informatoin(t_data **data, char **ar)
{
	init_data(data, ar);
	init_mutex(data);
	init_philos(data);
}
