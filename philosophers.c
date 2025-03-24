/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zalaksya <zalaksya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 02:31:33 by zalaksya          #+#    #+#             */
/*   Updated: 2025/03/24 03:39:42 by zalaksya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long get_current_time(void) {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}

void init_input(t_philo *init, char **ar)
{
	init->n_philo = ft_atoi(ar[0]);
	init->t_die = ft_atoi(ar[1]) * 1000;
	init->t_eat = ft_atoi(ar[2]) * 1000;
	init->t_sleep = ft_atoi(ar[3]) * 1000;
	if (ar[4])
		init->t_t_eat = ft_atoi(ar[4]);
	else
		init->t_t_eat = -1;
}
void init_philos(t_arg *prgrm, t_philo *philos, char **ar, pthread_mutex_t *forks)
{
	int i = 0;
	while(i < prgrm->philo->n_philo)
	{
		philos[i].id = i + 1;
		init_input(&philos[i], ar);
		philos[i].start_time = get_current_time();
		philos[i].last_meal = get_current_time();
		philos[i].dead = prgrm->dead_flag;
        philos[i].l_fork = &forks[i];
        philos[i].r_fork = &forks[(i + 1) % prgrm->philo->n_philo];
		philos[i].arg = prgrm;
		i++;
	}
}

void *routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;
    while (1)
	{
        printf("%ld %d is thinking\n", get_current_time() - philo->start_time, philo->id);
        pthread_mutex_lock(philo->l_fork);
        printf("%ld %d has taken a fork\n", get_current_time() - philo->start_time, philo->id);
        pthread_mutex_lock(philo->r_fork);
        printf("%ld %d has taken a fork\n", get_current_time() - philo->start_time, philo->id);
        printf("%ld %d is eating\n", get_current_time() - philo->start_time, philo->id);
        usleep(philo->t_eat);
        philo->last_meal = get_current_time();
        philo->meal_count++;
        pthread_mutex_unlock(philo->l_fork);
        pthread_mutex_unlock(philo->r_fork);
        printf("%ld %d is sleeping\n", get_current_time() - philo->start_time, philo->id);
        usleep(philo->t_sleep);
    }
    return NULL;
}

int create_thread(t_philo *philo)
{
	int	i;

	i = 0;
	pthread_t thread[philo->n_philo];
	while(i  < philo->n_philo)
	{
		if (!pthread_create(&thread[i], NULL, &routine, NULL))
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
	return (0);
}
// void init_mutex(t_arg *philo)
// {
// 	int	i;

// 	i = 0;
// 	while(i < philo->philo->n_philo)
// 	{
// 		if (!pthread_mutex_init(&philo->philo->forks[i], NULL))
// 			return (write(2, "feild to join a thread\n", 24), 1);
// 		i++;
// 	}
// }

void init_mutex(t_arg *philo)
{
    int i = 0;
	puts("\n\n\n\n");
	printf("n_philo :%d\n", philo->philo->n_philo);
    while (i < philo->philo->n_philo)
	{
        if (pthread_mutex_init(&philo->forks, NULL) != 0)
		{
            write(2, "Failed to initialize mutex\n", 27);
            return;
        }
        i++;
    }
    if (pthread_mutex_init(&philo->print_lock, NULL) != 0)
	{
        write(2, "Failed to initialize print mutex\n", 33);
        return;
    }
}

static char **parsing (char **av)
{
	char	*p;
	char	**ar;

	p = ft_check_join(av);
	if (!p)
		return (NULL);
	ar = ft_check_arg(&p);
	if (!ar)
		return (free(p), NULL);
	return (free(p), ar);
}
int	main(int ac, char **av)
{
	t_program		program;
	t_philo			philos[PHILO_MAX];
	pthread_mutex_t	forks[PHILO_MAX];
	t_philo	*philo = NULL;
	t_arg	*arg;
	char	**ar;

	arg = malloc(sizeof(t_philo));
	if (ac == 1)
		return (0);
	ar = parsing(av);
	if (!ar)
		return (free(arg), write(2, "Error\n", 6), 1);
	init_mutex(arg);
	init_philos(arg,  philo, ar, &arg->forks);
	create_thread(philo);
	//create_thread_and_mutexes(arg);
	free(arg);
	return (0);
}
