/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zalaksya <zalaksya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 16:09:19 by zalaksya          #+#    #+#             */
/*   Updated: 2025/05/26 18:56:57 by zalaksya         ###   ########.fr       */
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

void	init_data(t_data **data, char **ar)
{
	(*data)->philos = NULL;
	(*data)->n_philo = ft_atoi(ar[0]);
	(*data)->t_die = ft_atoi(ar[1]);
	(*data)->t_eat = ft_atoi(ar[2]);
	(*data)->t_sleep = ft_atoi(ar[3]);
}

void	start_routine(void *input)
{
	t_data *data;
	
	data = (t_data *)input;
	
	
	
}

void create_threads(t_data **data)
{
	int	i;

	i = 0;
	pthread_t thread[(*data)->n_philo];
	while (i < (*data)->n_philo)
	{
		pthread_create(&thread[i], NULL, start_routine, NULL);
		i++;
	}
}

int	main(int ac, char **av)
{
	t_data	*data;
	char	**ar;

	data = NULL;
	ar = NULL;
	data = malloc(sizeof(t_data));
	if (!data)
		return (0);
	if (ac != 5 && ac != 6)
		return (0);
	ar = parsing(av);
	if (!ar)
		return (write(2, "Error\n", 6), 1);
	init_data(&data, ar);
	ft_init_informatoin(&data);
	create_threads(&data);
	ft_free(ar);
	return (0);
}
