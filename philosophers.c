/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zalaksya <zalaksya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 02:31:33 by zalaksya          #+#    #+#             */
/*   Updated: 2025/03/22 03:01:24 by zalaksya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void create_thread_mutexes(t_arg *philo)
{
	int	i;

	i = 0;
	while (i < philo->n_philo)
	{
		pthread_mutex_init(&philo->forks[i], NULL);
		i++;
	}
	i = 0;
	pthread_t thread[philo->n_philo];
	philo->philo = malloc(sizeof(t_philo));
	while(i  < philo->n_philo)
	{
		if (!pthread_create(thread[i], NULL, &routine, NULL))
			return (write(2, "feild to create a thread\n", 26), 1);
		i++;
	}
	i = 0;
	while(i < philo->n_philo)
	{
		if (!pthread_join(thread[i], NULL))
			return (write(2, "feild to join a thread\n", 24), 1);
		i++;
	}
	
}

int	main(int ac, char **av)
{
	t_arg	*arg;

	arg = malloc(sizeof(t_arg));
	if (ac == 1)
		return (0);
	if (parsing(av, arg))
		return (write(2, "Error\n", 6), 1);
	create_thread_and_mutexes(arg);
	return (0);
}
