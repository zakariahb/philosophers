/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zalaksya <zalaksya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 02:31:33 by zalaksya          #+#    #+#             */
/*   Updated: 2025/03/28 01:08:09 by zalaksya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
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
typedef struct s_philo
{
	int				id;
	int				n_philo;
	size_t			t_die;
	size_t			t_eat;
	size_t			t_sleep;
	int				t_t_eat;
	size_t			s_time;
	int				n_meals;
	int				is_dead;
	int				right_fork;
	int				left_fork;
}	t_philo;

typedef struct s_data
{
	int				dead_flag;
	t_philo			*philos;
	pthread_t		thread;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_lock;
	struct s_data	*next;
}	t_data;


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
	nt	i;
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


size_t	get_current_time(void)
{
	struct timeval	time;
	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);	
}

// void *routine(void *arg)
// {
//    t_data*data = (t_philo *)arg;

//    while (1)
//    {
//        printf("%zu %d is thi
// 	   nking\n", (get_current_time() - data->philos->s_time) / 1000, data->philos->id);
//        // Pick up forks
//        pthread_mutex_lock(&data->forks[data->philos->left_fork]);
//        printf("%zu %d has taken a fork\n", (get_current_time() - data->s_time) / 1000, philo->id);
//        pthread_mutex_lock(&data->forks[right_fork]);
//        printf("%zu %d has taken a fork\n", (get_current_time() - data->start_time) / 1000, philo->id);

//        // Eat
//        printf("%zu %d is eating\n", (get_current_time() - data->start_time) / 1000, philo->id);
//        philo->last_meal_time = get_current_time();
//        usleep(data->time_t_eat * 1000);

//        // Put down forks
//        pthread_mutex_unlock(&data->forks[left_fork]);
//        pthread_mutex_unlock(&data->forks[right_fork]);

//        // Sleep
//        usleep(data->time_to_sleep * 1000);
//    }
//    return NULL;
//        printf("%ld %d is sleeping\n", (get_current_time() - data->start_time) / 1000, philo->id);
// }
// int create_thread_mutexes(t_data *data)
// {
// 	int	i;

// 	i = 0;
// 	while (i < data->philos->n_philo)
// 	{
// 		pthread_mutex_init(&data->forks[i], NULL);
// 		i++;
// 	}
// 	i = 0;
// 	pthread_t thread[data->philos->n_philo];
// 	data->philos = malloc(sizeof(t_philo));
// 	while(i  < data->philos->n_philo)
// 	{
// 		if (!pthread_create(thread[i], NULL, &routine, NULL))
// 			return (write(2, "feild to create a thread\n", 26), 1);
// 		i++;
// 	}
// 	i = 0;
// 	while(i < data->philos->n_philo)
// 	{
// 		if (!pthread_join(thread[i], NULL))
// 			return (write(2, "feild to join a thread\n", 24), 1);
// 		i++;
// 	}
// }

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
