/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 14:13:03 by mohammoh          #+#    #+#             */
/*   Updated: 2024/05/19 16:54:14 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <limits.h>
#include <stdbool.h>
#include <sys/time.h>

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
} t_opcode;

typedef struct s_fork
{
	pthread_mutex_t	mutex;
	int		fork_id; // for debugging
	int		is_taken;
} t_fork;

typedef struct s_simulation
{
	pthread_t			*threads;
	t_fork				*forks;
	pthread_mutex_t		*message;
	// pthread_mutex_t		*death;
	pthread_mutex_t		*stop;
	long long		start;
	int					philo_numbers;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					eat_counter;
	int					max_eat;
	int					is_dead;
	int					current_eat;
}				t_simulation;

typedef struct s_philo
{
	pthread_mutex_t	*eat;
	unsigned int	eating_time;
	unsigned int	next_meal;
	int				id;
	int				right_fork;
	int				left_fork;
	int				is_dead;
	int				eat_counter;
	int				max_eat;

	//who picked it last
	t_simulation	*simulation;
}				t_philo;


//parsing 
int				ft_parse(char **av, t_simulation *simulation);

//utils
void			ft_putstr_fd(char *s, int fd);
long			ft_atoi(char *str);
long long		ft_get_time(void);

//safe handle
void			ft_thread_handle(pthread_t *thread, t_opcode opcode , void *(*routine)(void *), void *arg);
void			ft_mutex_handle(pthread_mutex_t *mutex, t_opcode opcode);
void			*ft_save_malloc(size_t size);
int				ft_panic(char *message, int ret);

//initialization
t_philo			*ft_philo_init(t_simulation *simulation);
t_fork			*ft_fork_init(t_simulation *simulation);

//simulation
void			ft_start_simulation(t_philo *philo, t_simulation *simulation);
void			ft_print_message(t_philo *philo, t_simulation *simulation, int opcode, int fork_id);

//Operations
void			ft_thinking(t_philo philo, t_simulation *sim);
void			ft_sleeping(t_philo philo, t_simulation *sim);
void			ft_eating(t_philo *philo, t_simulation *sim);
bool			ft_isdead(t_philo philo, t_simulation *sim);

#endif