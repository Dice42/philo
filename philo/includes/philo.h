/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 14:13:03 by mohammoh          #+#    #+#             */
/*   Updated: 2024/05/26 12:48:54 by mohammoh         ###   ########.fr       */
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

/**
 * @brief this enum has all the operations that can be done
 * by the threads and mutexes
 */
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

/**
 * @brief this structure has all the information about the fork
 */
typedef struct s_fork
{
	pthread_mutex_t	mutex;
	int				last_picked;
	int				is_picked;
}	t_fork;

/**
 * @brief this structure has all the shared resources 
 * between the threads excluding the philosopher struct 
 * avoiding speaking to each other
 */
typedef struct s_simulation
{
	pthread_t			*threads;
	t_fork				*forks;
	pthread_mutex_t		*message;
	pthread_mutex_t		*stop;
	pthread_mutex_t		*done;
	size_t				start;
	size_t				time_to_die;
	size_t				time_to_eat;
	size_t				time_to_sleep;
	size_t				*last_meal;
	int					philo_numbers;
	int					eat_counter;
	int					max_eat;
	int					all_done;
	int					start_flag;
	int					current_eat;
	int					stop_simulation;
}				t_simulation;

/**
 * @brief this structure has all the information about the philosopher
 */
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

/* ************************************************************************** */
/*									PARSE UTILS								  */
/* ************************************************************************** */
int				ft_parse(char **av, t_simulation *simulation);
int				set_philosophers(t_simulation *simulation, int num);
int				set_time_to_die(t_simulation *simulation, int num);
int				set_time_to_eat(t_simulation *simulation, int num);
int				set_time_to_sleep(t_simulation *simulation, int num);
int				set_max_eat(t_simulation *simulation, int num);

/* ************************************************************************** */
/*									UTILS									  */
/* ************************************************************************** */
void			ft_putstr_fd(char *s, int fd);
long			ft_atoi(char *str);
void			ft_usleep(size_t ms, t_simulation *sim);
size_t			ft_time(void);
void			ft_free(t_simulation *sim);

/* ************************************************************************** */
/*								SAFE HANDLE									  */
/* ************************************************************************** */
void			ft_thread_handle(pthread_t *thread,
					t_opcode opcode, void *(*routine)(void *), void *arg);
void			ft_mutex_handle(pthread_mutex_t *mutex, t_opcode opcode);
void			*ft_save_malloc(size_t size);
int				ft_panic(char *message, int ret);

/* ************************************************************************** */
/*								INITILIZATING								  */
/* ************************************************************************** */
t_philo			*ft_philo_init(t_simulation *simulation);

/* ************************************************************************** */
/*								SIMULATION									  */
/* ************************************************************************** */
void			*thread_routine(void *data);
void			get_start_time(t_simulation *sim);
void			ft_start_simulation(t_philo *philo, t_simulation *simulation);
void			ft_print_message(t_philo *philo,
					t_simulation *simulation, int opcode);
void			ft_get_forks(t_philo *philo, t_simulation *sim);

/* ************************************************************************** */
/*								OPERATIONS									  */
/* ************************************************************************** */
void			ft_thinking(t_philo *philo);
void			ft_sleeping(t_philo *philo);
void			ft_eating(t_philo *philo);
void			check_philosopher_deaths(void *data);
int				ft_check_death_status(t_simulation *sim);

#endif