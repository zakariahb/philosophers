#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include <string.h>

typedef struct s_philo {
    int             id;
    int             n_philo;
    size_t          t_die;
    size_t          t_eat;
    size_t          t_sleep;
    int             t_t_eat;
    size_t          s_time;
    int             n_meals;
    int             is_dead;
    int             right_fork;
    int             left_fork;
    size_t          last_meal;
    pthread_t       thread;
    struct s_data   *data;
} t_philo;

typedef struct s_data {
    int             dead_flag;
    t_philo         *philos;
    pthread_mutex_t *forks;
    pthread_mutex_t print_lock;
    size_t          start_time;
} t_data;

// Utility functions
size_t  get_current_time(void) {
    struct timeval  time;
    gettimeofday(&time, NULL);
    return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int ft_atoi(const char *str) {
    int res = 0;
    while (*str) {
        res = res * 10 + (*str - '0');
        str++;
    }
    return res;
}

// Philosopher actions
void    print_status(t_philo *philo, char *msg) {
    pthread_mutex_lock(&philo->data->print_lock);
    if (!philo->data->dead_flag) {
        printf("%zu %d %s\n", 
              get_current_time() - philo->data->start_time, 
              philo->id, msg);
    }
    pthread_mutex_unlock(&philo->data->print_lock);
}

void    eat(t_philo *philo) {
    pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
    print_status(philo, "has taken a fork");
    
    pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
    print_status(philo, "has taken a fork");
    
    print_status(philo, "is eating");
    philo->last_meal = get_current_time();
    usleep(philo->t_eat * 1000);
    
    pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
    pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
    
    if (philo->t_t_eat > 0) {
        philo->n_meals++;
        if (philo->n_meals >= philo->t_t_eat) {
            return;
        }
    }
}

void    *philo_routine(void *arg) {
    t_philo *philo = (t_philo *)arg;
    
    if (philo->id % 2 == 0)
        usleep(1000);
        
    while (1) {
        print_status(philo, "is thinking");
        eat(philo);
        print_status(philo, "is sleeping");
        usleep(philo->t_sleep * 1000);
        
        if (philo->data->dead_flag || 
           (philo->t_t_eat > 0 && philo->n_meals >= philo->t_t_eat)) {
            break;
        }
    }
    return NULL;
}

// Monitoring
void    monitor_philos(t_data *data) {
    int i;
    int all_ate;
    
    while (!data->dead_flag) {
        all_ate = 1;
        i = -1;
        while (++i < data->philos[0].n_philo) {
            if (get_current_time() - data->philos[i].last_meal > data->philos[i].t_die) {
                print_status(&data->philos[i], "died");
                data->dead_flag = 1;
                break;
            }
            if (data->philos[i].t_t_eat > 0 && 
                data->philos[i].n_meals < data->philos[i].t_t_eat) {
                all_ate = 0;
            }
        }
        if (data->dead_flag || (data->philos[0].t_t_eat > 0 && all_ate)) {
            break;
        }
        usleep(1000);
    }
}

// Initialization
void    init_data(t_data *data, char **av) {
    int i;
    
    data->start_time = get_current_time();
    data->dead_flag = 0;
    data->philos = malloc(sizeof(t_philo) * ft_atoi(av[1]));
    data->forks = malloc(sizeof(pthread_mutex_t) * ft_atoi(av[1]));
    
    pthread_mutex_init(&data->print_lock, NULL);
    
    i = -1;
    while (++i < ft_atoi(av[1])) {
        pthread_mutex_init(&data->forks[i], NULL);
    }
    
    i = -1;
    while (++i < ft_atoi(av[1])) {
        data->philos[i].id = i + 1;
        data->philos[i].n_philo = ft_atoi(av[1]);
        data->philos[i].t_die = ft_atoi(av[2]);
        data->philos[i].t_eat = ft_atoi(av[3]);
        data->philos[i].t_sleep = ft_atoi(av[4]);
        data->philos[i].t_t_eat = (av[5]) ? ft_atoi(av[5]) : -1;
        data->philos[i].n_meals = 0;
        data->philos[i].left_fork = i;
        data->philos[i].right_fork = (i + 1) % ft_atoi(av[1]);
        data->philos[i].last_meal = data->start_time;
        data->philos[i].data = data;
    }
}

// Main execution
int main(int ac, char **av) {
    t_data  data;
    int     i;
    
    if (ac < 5 || ac > 6) {
        printf("Usage: %s number_of_philos time_to_die time_to_eat time_to_sleep [meals_needed]\n", av[0]);
        return 1;
    }
    
    init_data(&data, av);
    
    i = -1;
    while (++i < ft_atoi(av[1])) {
        pthread_create(&data.philos[i].thread, NULL, philo_routine, &data.philos[i]);
    }
    
    monitor_philos(&data);
    
    i = -1;
    while (++i < ft_atoi(av[1])) {
        pthread_join(data.philos[i].thread, NULL);
    }
    
    // Cleanup
    i = -1;
    while (++i < ft_atoi(av[1])) {
        pthread_mutex_destroy(&data.forks[i]);
    }
    pthread_mutex_destroy(&data.print_lock);
    free(data.philos);
    free(data.forks);
    
    return 0;
}