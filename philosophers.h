/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zalaksya <zalaksya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 01:47:20 by zalaksya          #+#    #+#             */
/*   Updated: 2025/03/19 03:26:51 by zalaksya         ###   ########.fr       */
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
	int			id;
	int			left_fork;
	int			right_fork;
	long		last_meal_time;
	int			meal_count;
	pthread_t	thread;
	struct s_arg *arg;
}	t_philo;

typedef struct s_arg
{
	int				n_philo;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				t_t_eat;
	int				is_dead;
	int				start_time;
	t_philo			*philo;
	long			start;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_lock;
}	t_arg;

char	*ft_strjoin(char *s1, const char *s2);
char	**ft_split(char const *s, char c);
char	*ft_strdup(const char *s1);
char	*ft_check_join(char **av);
int		ft_check_arg(char **str, t_arg *arg);
long	ft_atoi(const char *str);
void	ft_free(char **str);
int		ft_strlen(const char *str);

#endif