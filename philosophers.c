/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zalaksya <zalaksya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 16:09:19 by zalaksya          #+#    #+#             */
/*   Updated: 2025/07/03 10:45:58 by zalaksya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	destroy_mutex(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->n_philo)
		pthread_mutex_destroy(&data->forks[i]);
	pthread_mutex_destroy(&data->time_last_eat);
	pthread_mutex_destroy(&data->print_lock);
	pthread_mutex_destroy(&data->meals);
	pthread_mutex_destroy(&data->death_mutex);
}

int	create_threads(t_data *data)
{
	int	i;

	i = 0;
	data->start_simulation = get_current_time();
	while (i < data->n_philo)
	{
		if (pthread_create(&data->philos[i].thread,
				NULL, start_routine, &data->philos[i]))
			return (1);
		i++;
	}
	monitoring(data);
	i = 0;
	while (i < data->n_philo)
	{
		if (pthread_detach(data->philos[i].thread))
			return (1);
		i++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_data	*data;
	char	**ar;

	ar = NULL;
	if (ac != 5 && ac != 6)
		return (0);
	ar = parsing(av);
	if (!ar)
		return (write(2, "Error\n", 6), 1);
	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	if (ft_init_informatoin(&data, ar))
		return (1);
	if (create_threads(data))
		return (destroy_mutex(data), free_ar(data), 1);
	destroy_mutex(data);
	free_ar(data);
	return (0);
}
