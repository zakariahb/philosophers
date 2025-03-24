/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zalaksya <zalaksya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 01:47:20 by zalaksya          #+#    #+#             */
/*   Updated: 2025/03/24 03:34:36 by zalaksya         ###   ########.fr       */
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
	long			t_die;
	long			t_eat;
	long			t_sleep;
	long			t_t_eat;
	int				t_eaten;
	int				is_dead;
	int				start_time;
	int				dead;
	long			last_meal;
	int				meal_count;
	int				n_philo;
	pthread_t		thread;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	struct s_arg	*arg;
}	t_philo;

typedef struct s_arg
{
	t_philo			*philo;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	forks;
	int				dead_flag;
	long			start;
}	t_arg;



// Function prototypes
long get_current_time(void);

char	*ft_strjoin(char *s1, const char *s2);
char	**ft_split(char const *s, char c);
int		ft_strlen(const char *str);
char	*ft_strdup(const char *s1);
char	*ft_check_join(char **av);
char	**ft_check_arg(char **str);
long	ft_atoi(const char *str);
void	ft_free(char **str);

#endif