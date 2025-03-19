/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zalaksya <zalaksya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 02:31:33 by zalaksya          #+#    #+#             */
/*   Updated: 2025/03/19 15:55:58 by zalaksya         ###   ########.fr       */
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
void *routine(void *p)
{
	t_philo	*philo;
	t_arg	*arg;

	philo = (t_philo *)p;
	arg = philo->arg;

	while(!arg->is_dead)
	{
		print_status(philo, "is thinking");
		pthread_mutex_lock(&arg->forks[philo->left_fork]);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(&arg->forks[philo->right_fork]);
		print_status(philo, "has taken a fork");
		print_status(philo, "is eating");
		philo->last_meal_time = get_current_time();
		usleep(arg->t_eat);
		philo->meal_count++;
		pthread_mutex_unlock(&arg->forks[philo->left_fork]);
		pthread_mutex_unlock(&arg->forks[philo->right_fork]);
		print_status(philo, "is sleeping");
		usleep(arg->t_sleep);
		
	}
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

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <unistd.h>

typedef struct s_philosopher {
    int id;
    int left_fork;
    int right_fork;
    long last_meal_time;
    int meal_count;
    pthread_t thread;
    struct s_data *data;
} t_philosopher;

typedef struct s_data {
    int num_philosophers;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int must_eat_count;
    long start_time;
    int is_dead;
    pthread_mutex_t *forks;
    pthread_mutex_t print_mutex;
    t_philosopher *philosophers;
} t_data;

long get_current_time() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000000) + tv.tv_usec;
}

void print_status(t_philosopher *philo, char *status) {
    pthread_mutex_lock(&philo->data->print_mutex);
    if (!philo->data->is_dead) {
        printf("%ld %d %s\n", (get_current_time() - philo->data->start_time) / 1000, philo->id, status);
    }
    pthread_mutex_unlock(&philo->data->print_mutex);
}

void *philosopher_routine(void *arg) {
    t_philosopher *philo = (t_philosopher *)arg;
    t_data *data = philo->data;

    while (!data->is_dead) {
        print_status(philo, "is thinking");
        pthread_mutex_lock(&data->forks[philo->left_fork]);
        print_status(philo, "has taken a fork");
        pthread_mutex_lock(&data->forks[philo->right_fork]);
        print_status(philo, "has taken a fork");
        print_status(philo, "is eating");
        philo->last_meal_time = get_current_time();
        usleep(data->time_to_eat);
        philo->meal_count++;
        pthread_mutex_unlock(&data->forks[philo->left_fork]);
        pthread_mutex_unlock(&data->forks[philo->right_fork]);
        print_status(philo, "is sleeping");
        usleep(data->time_to_sleep);
    }
    return NULL;
}

void monitor_philosophers(t_data *data) {
    int i;
    while (!data->is_dead) {
        for (i = 0; i < data->num_philosophers; i++) {
            if (get_current_time() - data->philosophers[i].last_meal_time > data->time_to_die) {
                print_status(&data->philosophers[i], "died");
                data->is_dead = 1;
                return;
            }
        }
        usleep(1000);
    }
}

void init_simulation(t_data *data) {
    int i;
    data->forks = malloc(data->num_philosophers * sizeof(pthread_mutex_t));
    for (i = 0; i < data->num_philosophers; i++) {
        pthread_mutex_init(&data->forks[i], NULL);
    }
    pthread_mutex_init(&data->print_mutex, NULL);
    data->philosophers = malloc(data->num_philosophers * sizeof(t_philosopher));
    for (i = 0; i < data->num_philosophers; i++) {
        data->philosophers[i].id = i + 1;
        data->philosophers[i].left_fork = i;
        data->philosophers[i].right_fork = (i + 1) % data->num_philosophers;
        data->philosophers[i].last_meal_time = 0;
        data->philosophers[i].meal_count = 0;
        data->philosophers[i].data = data;
    }
    data->start_time = get_current_time();
    data->is_dead = 0;
}

void start_simulation(t_data *data) {
    int i;
    for (i = 0; i < data->num_philosophers; i++) {
        pthread_create(&data->philosophers[i].thread, NULL, philosopher_routine, &data->philosophers[i]);
    }
    monitor_philosophers(data);
    for (i = 0; i < data->num_philosophers; i++) {
        pthread_join(data->philosophers[i].thread, NULL);
    }
}

void cleanup_simulation(t_data *data) {
    int i;
    for (i = 0; i < data->num_philosophers; i++) {
        pthread_mutex_destroy(&data->forks[i]);
    }
    pthread_mutex_destroy(&data->print_mutex);
    free(data->forks);
    free(data->philosophers);
}

int main(int argc, char **argv) {
    if (argc < 5 || argc > 6) {
        printf("Usage: %s number_of_philosophers time_to_die time_to_eat time_to_sleep [must_eat_count]\n", argv[0]);
        return 1;
    }
    t_data data;
    data.num_philosophers = atoi(argv[1]);
    data.time_to_die = atoi(argv[2]) * 1000;
    data.time_to_eat = atoi(argv[3]) * 1000;
    data.time_to_sleep = atoi(argv[4]) * 1000;
    data.must_eat_count = argc == 6 ? atoi(argv[5]) : -1;
    init_simulation(&data);
    start_simulation(&data);
    cleanup_simulation(&data);
    return 0;
}