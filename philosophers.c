/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zalaksya <zalaksya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 16:09:19 by zalaksya          #+#    #+#             */
/*   Updated: 2025/05/27 15:05:04 by zalaksya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

size_t	get_current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

static char	**parsing(char **av)
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

void	print_message(pthread_mutex_t *print_lock, int id, char *str)
{
	pthread_mutex_lock(print_lock);
	printf("%d %s\n", id, str);
	pthread_mutex_unlock(print_lock);
}

void	*start_routine(void *input)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)input;
	data = philo->data;
	while (1)
	{
		if (philo->id % 2 == 0)
			usleep(100);
		pthread_mutex_lock(philo->l_fork);
		print_message(&data->print_lock, philo->id, "has taken a fork");
		pthread_mutex_lock(philo->r_fork);
		print_message(&data->print_lock, philo->id, "has taken a fork");
		print_message(&data->print_lock, philo->id, "is eating");
		usleep(data->t_eat * 1000);
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
		print_message(&data->print_lock, philo->id, "is sleeping");
		usleep(data->t_sleep * 1000);
		print_message(&data->print_lock, philo->id, "is thinking");
	}
	return (NULL);
}

int	create_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
	{
		if (pthread_create(&data->philos[i].thread, NULL, start_routine, &data->philos[i]) != 0)
			return (1);	
		i++;
	}
	i = 0;
	while (i < data->n_philo)
	{
		if (pthread_join(data->philos[i].thread, NULL) != 0)
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
	ft_init_informatoin(&data, ar);
	create_threads(data);
	ft_free(ar);
	return (0);
}

