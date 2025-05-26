/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zalaksya <zalaksya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 01:47:20 by zalaksya          #+#    #+#             */
/*   Updated: 2025/05/26 17:10:17 by zalaksya         ###   ########.fr       */
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
	int				is_dead;
	size_t			s_time;
	int				n_meals;
	pthread_mutex_t	right_fork;
	pthread_mutex_t	left_fork;
	struct s_philo	*next;
}	t_philo;

typedef struct s_data
{
	int				n_philo;
	int				t_t_eat;
	size_t			t_die;
	size_t			t_eat;
	size_t			t_sleep;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_lock;
}	t_data;

void	ft_init_informatoin(t_data **data);
void	ft_lstadd_back(t_philo **lst, t_philo *new);
char	*ft_strjoin(char *s1, const char *s2);
char	**ft_split(char const *s, char c);
int		ft_strlen(const char *str);
char	*ft_strdup(const char *s1);
char	*ft_check_join(char **av);
char	**ft_check_arg(char **str);
long	ft_atoi(const char *str);
void	ft_free(char **str);
t_philo	*lst_new();

#endif