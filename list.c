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

static t_philo	*ft_lstlast(t_data *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
	{
		lst = lst->next;
	}
	return (lst);
}

t_data *ft_lstnew(char **ar)
{
	static int	i;
	t_data		*data;

	i = i + 1;
	data = NULL;
	data = malloc(sizeof(t_philo));
	if (!data)
	return (NULL);
	data->philos->id = i;
	data->philos->n_philo = ft_atoi(ar[0]);
	data->philos->t_die = ft_atoi(ar[1]);
	data->philos->t_eat = ft_atoi(ar[2]);
	data->philos->t_sleep = ft_atoi(ar[3]);
	data->philos->start_time = 0;
	data->philos->is_dead = 0;
	data->philos->right_fork = i;
	data->philos->left_fork = data->philos->id - data->philos->n_philo;
	if (ar[4])
		data->philos->t_t_eat = ft_atoi(ar[4]);
	data-> next = NULL;
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

