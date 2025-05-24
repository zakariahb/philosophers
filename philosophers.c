
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

size_t	get_current_time(void)
{
	struct timeval	time;
	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);	
}

t_data *create_list(char **ar, t_data *data)
{
	int		i;

	i = -1;
	while(++i < ft_atoi(ar[1]))
	{
		ft_lstadd_back(&data, ft_lstnew(ar, data));
		i++;
	}
	return (data);
}

static char **parsing (char **av)
{
	char	*p;
	char	**ar = NULL;

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
	t_data	*data = NULL;
	char	**ar;
	data = malloc(sizeof(t_data));
	if (!data)
	     return (0);

	if (ac != 5 && ac != 6)
		return (0);
	ar = parsing(av);
	if (!ar)
		return (write(2, "Error\n", 6), 1);
	data =  create_list(av , data);
	// create_thread_and_mutexes(data);
	// init_philos(philo);

	// while (data->philos)
	// {
		printf("data : %d\n", (*data).philos->id);
		// data = data->next;
	// }

	
	return (0);
}
