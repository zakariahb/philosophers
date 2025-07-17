/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zalaksya <zalaksya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 01:47:20 by zalaksya          #+#    #+#             */
/*   Updated: 2025/07/17 09:44:14 by zalaksya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include "stdio.h"
# include "unistd.h"
# include "stdlib.h"
# include "limits.h"
# include "pthread.h"
# include "sys/time.h"

typedef struct s_philo
{
	int				id;
	int				eating;
	pthread_t		thread;
	int				meals_eaten;
	size_t			last_meal_time;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	struct s_data	*data;
}	t_philo;

typedef struct s_data
{
	int				n_philo;
	size_t			t_die;
	size_t			start_simulation;
	size_t			t_eat;
	int				t_t_eat;
	size_t			t_sleep;
	int				max_meals;
	int				someone_died;
	int				eating_enough;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	meals;
	pthread_mutex_t	eating;
	pthread_mutex_t	time_last_eat;
	pthread_mutex_t	*forks;
	t_philo			*philos;
}	t_data;

void	marque_as_died(t_data *data, int id, char *str);
void	print_message(t_data *data, char *str, int id);
int		ft_init_informatoin(t_data *data, char **ar);
int		check_one_philo(t_data *data, int id);
int		ft_usleep(size_t time, t_data *data);
void	init_data(t_data *data, char **ar);
int		checking_dead(t_data *data);
void	*start_routine(void *input);
void	destroy_mutex(t_data *data);
int		monitoring(t_data	*data);
long	ft_atoi(const char *str);
size_t	get_current_time(void);
size_t	get_current_time(void);
int		parsing(char **str);

#endif