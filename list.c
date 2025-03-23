/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zalaksya <zalaksya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 16:09:19 by zalaksya          #+#    #+#             */
/*   Updated: 2025/03/23 15:54:59 by zalaksya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static t_philo	*ft_lstlast(t_philo *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
	{
		lst = lst->next;
	}
	return (lst);
}

t_philo	*ft_lstnew(char **ar)
{
	static int	i;
	t_philo	*head;

	i = 0;
	head = malloc(sizeof(t_philo));
	if (!head)
		return (NULL);
	head->id = i + 1;
	head->n_philo = ft_atoi(ar[0]);
	head->t_die = ft_atoi(ar[1]) * 1000;
	head->t_eat = ft_atoi(ar[2]) * 1000;
	head->t_sleep = ft_atoi(ar[3]) * 1000;
	if (ar[4])
		head->t_t_eat = ft_atoi(ar[4]);
	head-> next = NULL;
	return (head);
}

void	ft_lstadd_back(t_philo **lst, t_philo *new)
{
	t_philo	*temp;

	if (!lst || !new)
		return ;
	temp = ft_lstlast(*lst);
	if (!temp)
		*lst = new;
	else
		temp->next = new;
}