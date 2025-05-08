/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zalaksya <zalaksya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 16:09:19 by zalaksya          #+#    #+#             */
/*   Updated: 2025/03/28 03:13:16 by zalaksya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static t_data	*ft_lstlast(t_data *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
	{
		lst = lst->next;
	}
	return (lst);
}

// typedef struct s_philo
// {
// 	int				id;
// 	int				n_philo;
// 	size_t			t_die;
// 	size_t			t_eat;
// 	size_t			t_sleep;
// 	int				t_t_eat;
// 	size_t			s_time;
// 	int				n_meals;
// 	int				is_dead;
// 	int				right_fork;
// 	int				left_fork;
// }	t_philo;

// typedef struct s_data
// {
// 	int				dead_flag;
// 	t_philo			*philos;
// 	pthread_t		thread;
// 	pthread_mutex_t	*forks;
// 	pthread_mutex_t	print_lock;
// 	struct s_data	*next;
// }	t_data;
t_data *ft_lstnew(char **ar, t_data *data)
{
	static int	i;
	i = i + 1;
	data->philos = malloc(sizeof(t_philo));
	if (!data)
		return (NULL);
	(*data).philos->n_philo = ft_atoi(ar[1]);
	(*data).philos->id = i;
	(*data).philos->t_die = ft_atoi(ar[2]);
	(*data).philos->t_eat = ft_atoi(ar[3]);
	(*data).philos->t_sleep = ft_atoi(ar[4]);
	(*data).philos->s_time = 0;
	(*data).philos->is_dead = 0;
	(*data).philos->left_fork = i;
	(*data).philos->right_fork = (i + 1) % (*data).philos->n_philo;
	if (ar[5])
		(*data).philos->t_t_eat = ft_atoi(ar[5]);
	(*data).next = NULL;
	return (data);
}

void	ft_lstadd_back(t_data **lst, t_data *new)
{
	t_data	*temp;

	if (!lst || !new)
		return ;
	temp = ft_lstlast(*lst);
	if (!temp)
		*lst = new;
	else
		temp->next = new;
}

