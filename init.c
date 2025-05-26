/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zalaksya <zalaksya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 16:16:50 by zalaksya          #+#    #+#             */
/*   Updated: 2025/05/26 08:29:00 by zalaksya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_init_informatoin(t_philo **data, char **ar)
{
	static int	i;

	i = i + 1;
	(*data)->n_philo = ft_atoi(ar[0]);
	(*data)->id = i;
	(*data)->t_die = ft_atoi(ar[1]);
	(*data)->t_eat = ft_atoi(ar[2]);
	(*data)->t_sleep = ft_atoi(ar[3]);
	(*data)->s_time = 0;
	(*data)->n_meals = 0;
	(*data)->is_dead = 0;
	(*data)->left_fork = i;
	(*data)->right_fork = (i + 1) % (*data)->n_philo;
	if (ar[4])
		(*data)->t_t_eat = ft_atoi(ar[4]);
	else
		(*data)->t_t_eat = -1;
}
