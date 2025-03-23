/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zalaksya <zalaksya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 02:31:33 by zalaksya          #+#    #+#             */
/*   Updated: 2025/03/23 15:54:46 by zalaksya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"


//void *philosopher_routine(void *arg) {
//    t_philosopher *philo = (t_philosopher *)arg;
//    t_data *data = philo->data;
//    int left_fork = philo->id;
//    int right_fork = (philo->id + 1) % data->num_philosophers;

//    while (!data->is_dead) {
//        // Think
//        printf("%ld %d is thinking\n", (get_current_time() - data->start_time) / 1000, philo->id);
//        usleep(1000000);

//        // Pick up forks
//        pthread_mutex_lock(&data->forks[left_fork]);
//        printf("%ld %d has taken a fork\n", (get_current_time() - data->start_time) / 1000, philo->id);
//        pthread_mutex_lock(&data->forks[right_fork]);
//        printf("%ld %d has taken a fork\n", (get_current_time() - data->start_time) / 1000, philo->id);

//        // Eat
//        printf("%ld %d is eating\n", (get_current_time() - data->start_time) / 1000, philo->id);
//        philo->last_meal_time = get_current_time();
//        usleep(data->time_to_eat * 1000);

//        // Put down forks
//        pthread_mutex_unlock(&data->forks[left_fork]);
//        pthread_mutex_unlock(&data->forks[right_fork]);

//        // Sleep
//        printf("%ld %d is sleeping\n", (get_current_time() - data->start_time) / 1000, philo->id);
//        usleep(data->time_to_sleep * 1000);
//    }
//    return NULL;
//}
//void create_thread_mutexes(t_arg *philo)
//{
//	int	i;

//	i = 0;
//	while (i < philo->n_philo)
//	{
//		pthread_mutex_init(&philo->philo->forks[i], NULL);
//		i++;
//	}
//	i = 0;
//	pthread_t thread[philo->n_philo];
//	philo->philo = malloc(sizeof(t_philo));
//	while(i  < philo->n_philo)
//	{
//		if (!pthread_create(thread[i], NULL, &routine, NULL))
//			return (write(2, "feild to create a thread\n", 26), 1);
//		i++;
//	}
//	i = 0;
//	while(i < philo->n_philo)
//	{
//		if (!pthread_join(thread[i], NULL))
//			return (write(2, "feild to join a thread\n", 24), 1);
//		i++;
//	}
//	i = 0;
//	while(i < philo->n_philo)
//	{
//		if (!pthread_mutex_init(&philo->philo->forks[i], NULL))
//			return (write(2, "feild to join a thread\n", 24), 1);
//		i++;
//	}
//}
static int parsing (char **av, t_philo *arg)
{
	char	*p;

	p = ft_check_join(av);
	if (!p)
		return (free(arg), 1);
	if (ft_check_arg(&p))
		return (free(p), 1);
	return (free(p), 0);
}
int	main(int ac, char **av)
{
	t_philo	*arg;

	arg = malloc(sizeof(t_philo));
	if (ac == 1)
		return (0);
	if (parsing(av, arg))
		return (free(arg), write(2, "Error\n", 6), 1);
	//create_thread_and_mutexes(arg);
	free(arg);
	return (0);
}
