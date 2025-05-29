/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zalaksya <zalaksya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 16:09:19 by zalaksya          #+#    #+#             */
/*   Updated: 2025/05/29 15:16:43 by zalaksya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

time_t	get_current_time(void)
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

void	print_message(t_data *data, char *str, int id)
{
	pthread_mutex_lock(&data->print_lock);
	printf("%zu %d %s\n", get_current_time() - data->start_simulation ,id, str);
	if (!strcmp(str, "died"))
		return ;
	pthread_mutex_unlock(&data->print_lock);
}

void	*start_routine(void *input)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)input;
	data = philo->data;
	if (!philo->id % 2)
		usleep(100);
	while (!data->simulation_ended)
	{
		pthread_mutex_lock(data->philos->l_fork);
		print_message(data, "has left taken fork", philo->id);
		pthread_mutex_lock(data->philos->r_fork);
		print_message(data, "has right taken fork", philo->id);
		print_message(data, "is eating", philo->id);
		pthread_mutex_lock(&data->meals);
		philo->meals_eaten++;
		philo->last_meal_time = get_current_time();
		pthread_mutex_unlock(&data->meals);
		usleep(data->t_eat);
		pthread_mutex_unlock(data->philos->l_fork);
		pthread_mutex_unlock(data->philos->r_fork);
		print_message(data, "is sleeping", philo->id);
		usleep(data->t_sleep);
		print_message(data, "is thinking", philo->id);
	}
	return (NULL);

}
// void *monitoring(void *monitor)
// {
// 	t_philo *philo;
// 	t_data *data;
// 	int i;
	
// 	philo = NULL;
// 	data = (t_data *)monitor;
// 	while (1)
// 	{
// 		i = 0;
// 		while (i < data->n_philo)
// 		{
// 			// philo = data->philos[i];
// 			pthread_mutex_lock(&data->meals);
// 			if (get_current_time() - data->philos[i].last_meal_time >= data->t_die)
// 			{
// 				print_message(data, "his dead");
// 				exit(0);
// 			}
// 			pthread_mutex_unlock(&data->meals);
// 			i++;
// 		}
// 		usleep(100);
// 	}
// 	return (NULL);
	
// }

void *monitoring(void *monitor)
{
    t_data *data = (t_data *)monitor;
    int i;
	// long long time;
    
    while (1)
    {
        i = 0;
        while (i < data->n_philo)
        {
            pthread_mutex_lock(&data->meals);
			// printf("%ld\n", data->philos[i].last_meal_time);
            if (get_current_time() - data->philos[i].last_meal_time >= data->t_die)
            {
                print_message(data, "died", data->philos[i].id);
                pthread_mutex_lock(&data->death_mutex);
                data->simulation_ended = 1;
                pthread_mutex_unlock(&data->death_mutex);
                pthread_mutex_unlock(&data->meals);
                return NULL;
            }
            pthread_mutex_unlock(&data->meals);
            i++;
        }
        usleep(1000); 
    }
    return NULL;
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
	return (0);
}

