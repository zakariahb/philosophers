/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zalaksya <zalaksya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 16:09:19 by zalaksya          #+#    #+#             */
/*   Updated: 2025/06/01 17:20:37 by zalaksya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int64_t	get_current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}


int	ft_usleep(useconds_t time)
{
	u_int64_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < time)
		usleep(time / 10);
	return (0);
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

int	print_message(t_data *data, char *str, int id)
{
	pthread_mutex_lock(&data->print_lock);
	printf("%llu %d %s\n", get_current_time() - data->start_simulation ,id, str);
	pthread_mutex_unlock(&data->print_lock);
	if (!strcmp(str, "died"))
		return (1);
	return (0);
}

void	*start_routine(void *input)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)input;
	data = philo->data;
	if (philo->id % 2 == 0)
		usleep(500);
	while (!data->simulation_ended)
	{
		pthread_mutex_lock(&data->death_mutex);
		if (data->simulation_ended)
		{
			pthread_mutex_unlock(&data->death_mutex);
			break;
		}
		pthread_mutex_unlock(&data->death_mutex);
		pthread_mutex_lock(philo->l_fork);
		print_message(data, "has left taken fork", philo->id);
		pthread_mutex_lock(philo->r_fork);
		print_message(data, "has right taken fork", philo->id);
		print_message(data, "is eating", philo->id);
		ft_usleep(data->t_eat);
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_lock(&data->meals);
		philo->meals_eaten++;
		philo->last_meal_time = get_current_time();
		pthread_mutex_unlock(&data->meals);
		print_message(data, "is sleeping", philo->id);
		ft_usleep(data->t_sleep);
		
		print_message(data, "is thinking", philo->id);
	}
	return (NULL);

}

void *monitoring(void *monitor)
{
	t_data *data = (t_data *)monitor;
	int	i;
	int	meals_eaten;

	meals_eaten = 0;
	while (1)
	{
		i = 0;
		while (i < data->n_philo)
		{
			int64_t time = get_current_time() - data->philos[i].last_meal_time;
			if (time > INT_MAX)
				time = 0;
			if (time >= data->t_die)
			{
				print_message(data, "died", data->philos[i].id);
				pthread_mutex_lock(&data->death_mutex);
				data->simulation_ended = 1;
				pthread_mutex_unlock(&data->death_mutex);
				return (NULL);
			}
			if (data->t_t_eat > 0 && data->t_t_eat == data->philos[i].meals_eaten)
				meals_eaten = 1;
			i++;
		}
		if (data->t_t_eat > 0 && meals_eaten)
		{
			pthread_mutex_lock(&data->death_mutex);	
			data->simulation_ended = 1;
			pthread_mutex_unlock(&data->death_mutex);	
			break ;
		}
		usleep(100); 
	}
	return (NULL);
}

int	create_threads(t_data *data)
{
	pthread_t monitor;
	int	i;

	i = 0;
	data->start_simulation = get_current_time();
	while (i < data->n_philo)
	{
		if (pthread_create(&data->philos[i].thread, NULL, start_routine, &data->philos[i]) != 0)
			return (1);
		i++;
	}
	if (pthread_create(&monitor, NULL, monitoring, data) != 0)
		return (1);
	i = 0;
	if (pthread_join(monitor, NULL) != 0)
		return (1);
	while (i < data->n_philo)
	{
		if (pthread_detach(data->philos[i].thread) != 0)
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
	// ft_free(data->philos);

	// free(data);
	// free(data);
	return (0);
}
