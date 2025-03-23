/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zalaksya <zalaksya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 01:47:20 by zalaksya          #+#    #+#             */
/*   Updated: 2025/03/23 15:53:35 by zalaksya         ###   ########.fr       */
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


//typedef struct s_philo
//{
//	int			id;
//	int			left_fork;
//	int			right_fork;
//	long		last_meal_time;
//	int			meal_count;
//	pthread_t	thread;
//	struct s_arg *arg;
//}	t_philo;

//typedef struct s_arg
//{
//	int				n_philo;
//	int				t_die;
//	int				t_eat;
//	int				t_sleep;
//	int				t_t_eat;
//	int				is_dead;
//	int				start_time;
//	t_philo			*philo;
//	long			start;
//	pthread_mutex_t	*forks;
//	pthread_mutex_t	print_lock;
//}	t_philo;


typedef struct s_philo
{
	int				id;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				t_t_eat;
	int				is_dead;
	int				start_time;
	int				left_fork;
	int				right_fork;
	long			last_meal_time;
	int				meal_count;
	int				n_philo;
	pthread_t		thread;
	struct s_arg	*arg;
	struct s_philo	*next;
	pthread_mutex_t	*forks;
}	t_philo;

typedef struct s_arg
{
	t_philo			*philo;
	pthread_mutex_t	print_lock;
	long			start;
}	t_arg;

void	ft_lstadd_back(t_philo **lst, t_philo *new);
char	*ft_strjoin(char *s1, const char *s2);
char	**ft_split(char const *s, char c);
int		ft_strlen(const char *str);
char	*ft_strdup(const char *s1);
char	*ft_check_join(char **av);
int		ft_check_arg(char **str);
long	ft_atoi(const char *str);
t_philo	*ft_lstnew(char **ar);
void	ft_free(char **str);

#endif