/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zalaksya <zalaksya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 01:47:20 by zalaksya          #+#    #+#             */
/*   Updated: 2025/07/01 21:02:10 by zalaksya         ###   ########.fr       */
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

# include <string.h>

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
	pthread_mutex_t	time_last_eat;
	pthread_mutex_t	*forks;
	t_philo			*philos;
}	t_data;

int		print_message(t_data *data, char *str, int id);
void	ft_init_informatoin(t_data **data, char **ar);
char	*ft_strjoin(char *s1, const char *s2);
void	init_data(t_data **data, char **ar);
char	**ft_split(char const *s, char c);
int		checking_dead(t_philo *philo);
void	*start_routine(void *input);
void	*monitoring(void *monitor);
int		ft_strlen(const char *str);
char	*ft_strdup(const char *s1);
char	**ft_check_arg(char **str);
char	*ft_check_join(char **av);
long	ft_atoi(const char *str);
size_t	get_current_time(void);
int		ft_usleep(size_t time);
size_t	get_current_time(void);
char	**parsing(char **av);
void	ft_free(char **str);

#endif