/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zalaksya <zalaksya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 16:09:19 by zalaksya          #+#    #+#             */
/*   Updated: 2025/05/26 08:27:59 by zalaksya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

size_t	get_current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

static char	**parsing(char **av)
{
	char	*p;
	char	**ar;

	ar = NULL;
	p = ft_check_join(av);
	if (!p)
		return (NULL);
	ar = ft_check_arg(&p);
	free(p);
	if (!ar)
		return (NULL);
	return (ar);
}

int	main(int ac, char **av)
{
	t_philo	*data;
	char	**ar;

	data = NULL;
	ar = NULL;
	data = malloc(sizeof(t_philo));
	if (!data)
		return (0);
	if (ac != 5 && ac != 6)
		return (0);
	ar = parsing(av);
	if (!ar)
		return (write(2, "Error\n", 6), 1);
	ft_init_informatoin(&data, ar);
	ft_free(ar);
	printf("%d\n", data->id);
	printf("%d\n", data->is_dead);
	printf("%d\n", data->right_fork);
	printf("%d\n", data->left_fork);
	printf("%d\n", data->n_meals);
	printf("%ld\n", data->t_sleep);
	printf("%ld\n", data->t_eat);
	printf("%d\n", data->t_t_eat);
	printf("%ld\n", data->s_time);
	return (0);
}
