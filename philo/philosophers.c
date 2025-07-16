/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zalaksya <zalaksya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 16:09:19 by zalaksya          #+#    #+#             */
/*   Updated: 2025/07/16 09:50:32 by zalaksya         ###   ########.fr       */
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

int	check_one_philo(t_data *data, int id)
{
	if (data->n_philo == 1)
	{
		ft_usleep(data->t_die, data);
		pthread_mutex_unlock(data->philos[0].l_fork);
		marque_as_died(data, id, "died");
		return (0);
	}
	return (1);
}

int	main(int ac, char **av)
{
	t_data	*data;
	char	**ar;

	ar = NULL;
	if (ac != 5 && ac != 6)
		return (write(2, "Error : ivalid argunments number\n", 34), 1);
	ar = parsing(av);
	if (!ar)
		return (write(2, "Error\n", 6), 1);
	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	if (ft_init_informatoin(data, ar))
		return (1);
	return (free(data), 0);
}
