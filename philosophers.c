/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zalaksya <zalaksya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 02:31:33 by zalaksya          #+#    #+#             */
/*   Updated: 2025/03/19 03:28:48 by zalaksya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	parsing(char **str, t_arg *arg)
{
	char	*p;

	p = ft_check_join(str);
	if (ft_check_arg(&p, arg))
		return (1);
	return (0);
}
void *routine()
{
	printf("zakaria is the best\n");
	return (NULL);
}

void	create_tread_and_mutexes(t_arg *data)
{
	int	i;

	i = 0;
	data->forks = malloc(data->n_philo * sizeof(pthread_mutex_t));
	while(i < data->n_philo)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&data->print_lock, NULL);
	data->philo = malloc(data->n_philo * sizeof(t_philo));
	i = 0;
	while(i < data->n_philo)
	{
		data->philo[i].id = i + 1;
		data->philo[i].left_fork = i;
		data->philo[i].right_fork = (i + 1) % data->n_philo ;
		data->philo[i].last_meal_time = 0;
		data->philo[i].meal_count = 0;
		data->philo[i].arg = data;
	}
	data->start_time = get_current_time();
    data->is_dead = 0;
}

long get_current_time()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000000) + tv.tv_usec;
}
void	*philo_rooute(void *arg)
{
	
}
int	main(int ac, char **av)
{
	t_arg	*arg;

	arg = malloc(sizeof(t_arg));
	if (ac == 1)
		return (0);
	if (parsing(av, arg))
		return (write(2, "Error\n", 6), 1);
	create_tread_and_mutexes(arg);
	
	// pthread_create();
	pthread_t i ; //j; // store the information about the tread 
	pthread_create(&i , NULL, &routine, NULL);
	//pthread_create(&j , NULL, &routine, NULL);
	pthread_join(i,  NULL);
	//pthread_join(j,  NULL);
	printf("d :%d\n", arg->t_die);
	return (0);
}
