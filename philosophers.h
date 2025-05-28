/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zalaksya <zalaksya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 01:47:20 by zalaksya          #+#    #+#             */
/*   Updated: 2025/05/28 09:18:39 by zalaksya         ###   ########.fr       */
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
	pthread_t		thread;
	int				n_meals;
	size_t			last_meal_time;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	struct s_data	*data;
}	t_philo;

typedef struct s_data
{
	int				n_philo;
	size_t			t_die;
	size_t			t_eat;
	size_t			t_sleep;
	int				max_meals;
	int				someone_died;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	*forks;
	t_philo			*philos;
}	t_data;

void	ft_init_informatoin(t_data **data, char **ar);
char	*ft_strjoin(char *s1, const char *s2);
void	init_data(t_data **data, char **ar);
char	**ft_split(char const *s, char c);
int		ft_strlen(const char *str);
char	*ft_strdup(const char *s1);
char	*ft_check_join(char **av);
char	**ft_check_arg(char **str);
long	ft_atoi(const char *str);
void	ft_free(char **str);

#endif