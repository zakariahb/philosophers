/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zalaksya <zalaksya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 16:09:19 by zalaksya          #+#    #+#             */
/*   Updated: 2025/05/26 17:10:06 by zalaksya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static t_philo	*ft_lstlast(t_philo *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

t_philo	*lst_new()
{
	static int	i;
	t_philo		*philo;


	philo = malloc(sizeof(t_philo));
	i = i + 1;
	philo->id = i;
	philo->s_time = 0;
	philo->n_meals = 0;
	philo->is_dead = 0;
	philo->next = NULL;
	return (philo);
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
