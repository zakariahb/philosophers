/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zalaksya <zalaksya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 02:31:33 by zalaksya          #+#    #+#             */
/*   Updated: 2025/03/18 22:21:33 by zalaksya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	parsing(char **str, t_arg *arg)
{
	char	*p;

	p = ft_check_join(str);
	if (ft_check_arg(&p, arg))
		return (1);
	return (0);
}
void *routine()
{
	printf("zakaria is the best\n");
	return (NULL);
}
int	main(int ac, char **av)
{
	t_arg	*arg;

	// pthread_create();
	pthread_t i ; //j; // store the information about the tread 
	pthread_create(&i , NULL, &routine, NULL);
	//pthread_create(&j , NULL, &routine, NULL);
	pthread_join(i,  NULL);
	//pthread_join(j,  NULL);
	arg = malloc(sizeof(t_arg));
	if (ac == 1)
		return (0);
	if (parsing(av, arg))
		return (write(2, "Error\n", 6), 1);
	return (0);
}
