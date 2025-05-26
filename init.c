/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zalaksya <zalaksya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 16:16:50 by zalaksya          #+#    #+#             */
/*   Updated: 2025/05/26 18:13:15 by zalaksya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_mutex(t_data **data)
{
	int	i;

	i = 0;
	while ((*data)->n_philo--)
		pthread_mutex_init(&(*data)->forks[i], NULL);
}

void	ft_init_informatoin(t_data **data)
{
	while ((*data)->n_philo--)
		ft_lstadd_back(&(*data)->philos, lst_new());
	init_mutex(data);
}
