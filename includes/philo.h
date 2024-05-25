/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 14:13:03 by mohammoh          #+#    #+#             */
/*   Updated: 2024/05/25 12:44:01 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <limits.h>
# include <stdbool.h>
# include <sys/time.h>

# define YES 1
# define NO 0
# define FORK 2
# define EATING 3
# define SLEEPING 4
# define THINKING 5
# define DIED 6
# define DONE 7

/* operation code enum */
typedef enum s_opcode
{
	INIT,
	DESTROY,
	LOCK,
	UNLOCK,
	CREATE,
	JOIN,
	DETACH,
	START,
	ONGOING
}	t_opcode;

typedef struct s_fork
{
	pthread_mutex_t	mutex;
	int				fork_id;
	int				last_picked;
	int				is_picked;
}	t_fork;

typedef struct s_simulation
{
	pthread_t			*threads;
	t_fork				*forks;
	pthread_mutex_t		*message;
	pthread_mutex_t		*death;
	pthread_mutex_t		*stop;
	size_t				start;
	int					philo_numbers;
	size_t				time_to_die;
	size_t				time_to_eat;
	size_t				time_to_sleep;
	int					eat_counter;
	int					max_eat;
	int					is_dead;
	int					start_flag;
	int					current_eat;
	size_t				*last_meal;
	int					stop_simulation;
}				t_simulation;

typedef struct s_philo
{
	unsigned int	eating_time;
	int				id;
	int				right_fork;
	int				left_fork;
	int				has_eaten;
	int				start;
	int				eat_counter;
	int				max_eat;
	int				is_one;
	t_simulation	*simulation;
}				t_philo;

//parsing 
int				ft_parse(char **av, t_simulation *simulation);
int				set_philosophers(t_simulation *simulation, int num);
int				set_time_to_die(t_simulation *simulation, int num);
int				set_time_to_eat(t_simulation *simulation, int num);
int				set_time_to_sleep(t_simulation *simulation, int num);
int				set_max_eat(t_simulation *simulation, int num);

//utils
void			ft_putstr_fd(char *s, int fd);
long			ft_atoi(char *str);
void			ft_usleep(size_t ms, t_simulation *sim);
size_t			ft_time(void);
void			ft_free(t_simulation *sim);

//safe handle
void			ft_thread_handle(pthread_t *thread,
					t_opcode opcode, void *(*routine)(void *), void *arg);
void			ft_mutex_handle(pthread_mutex_t *mutex, t_opcode opcode);
void			*ft_save_malloc(size_t size);
int				ft_panic(char *message, int ret);

//initialization
t_philo			*ft_philo_init(t_simulation *simulation);
t_fork			*ft_fork_init(t_simulation *simulation);

//simulation
void			*thread_routine(void *data);
void			get_start_time(t_simulation *sim);
void			ft_start_simulation(t_philo *philo, t_simulation *simulation);
void			ft_print_message(t_philo *philo,
					t_simulation *simulation, int opcode);

//Operations
void			ft_thinking(t_philo *philo);
void			ft_sleeping(t_philo *philo);
void			ft_eating(t_philo *philo);
void			check_philosopher_deaths(void *data);

//get_fork
void			ft_get_forks(t_philo *philo, t_simulation *sim);
void			ft_get_forks2(int first_fork, int second_fork,
					t_philo *philo, t_simulation *sim);

int				ft_check_death_status(t_simulation *sim);

#endif