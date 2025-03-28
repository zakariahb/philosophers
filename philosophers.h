/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zalaksya <zalaksya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 01:47:20 by zalaksya          #+#    #+#             */
/*   Updated: 2025/03/28 02:39:32 by zalaksya         ###   ########.fr       */
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
	int				n_philo;
	size_t			t_die;
	size_t			t_eat;
	size_t			t_sleep;
	int				t_t_eat;
	int				n_meals;
	size_t			start_time;
	int				is_dead;
	pthread_t		thread;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
}	t_philo;

typedef struct s_data
{
	int				dead_flag;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_lock;
	struct s_data *next;
}	t_data;



void	ft_lstadd_back(t_philo **lst, t_philo *new);
char	*ft_strjoin(char *s1, const char *s2);
char	**ft_split(char const *s, char c);
int		ft_strlen(const char *str);
char	*ft_strdup(const char *s1);
char	*ft_check_join(char **av);
char	**ft_check_arg(char **str);
long	ft_atoi(const char *str);
t_philo	*create_list(char **ar, t_data *data);
t_philo	*ft_lstnew(char **ar);
void	ft_free(char **str);

#endif