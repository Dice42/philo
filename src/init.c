/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 16:08:27 by mohammoh          #+#    #+#             */
/*   Updated: 2024/05/24 22:53:31 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
/** still need work
 * @brief this function will assign the forks to the philo
 * 
 * @param philo 
 * @param simulation 
 * @param i 
 */
void	assing_forks(t_philo *philo, t_simulation *simulation, int i)
{
	if (i == 0)
	{
		philo[i].left_fork = simulation->philo_numbers - 1;
		philo[i].right_fork = i;
	}
	else
	{
		philo[i].left_fork = i - 1;
		philo[i].right_fork = i;
	}
}
/**
 * @brief this function will initialize the philo struct
 * 
 *
 * @param simulation  
 * @return t_philo* 
 */
t_philo	*ft_philo_init(t_simulation *simulation)
{
	t_philo	*philo;
	int		i;
	
	i = 0;
	simulation->threads = ft_save_malloc(sizeof(pthread_t) * simulation->philo_numbers);
	simulation->forks = ft_fork_init(simulation);
	philo = ft_save_malloc(sizeof(t_philo) * simulation->philo_numbers);
	simulation->start_flag = 0;
	simulation->stop_simulation = 0;
	while (i < simulation->philo_numbers)
	{
		philo[i].id = i + 1;
		philo[i].eating_time = simulation->time_to_eat;
		philo[i].next_meal = 0; // NEXT MEAL
		philo[i].eat_counter = 0;
		philo[i].is_dead = NO;
		// philo[i].has_both_forks = NO;
		philo[i].has_eaten = NO;
		philo[i].max_eat = simulation->max_eat;
		assing_forks(philo, simulation, i);
		i++;
	}
	return (philo);
}
/**
 * @brief this function will initialize the fork struct
 * 
 * @param simulation
 * @return 
 */
t_fork	*ft_fork_init(t_simulation *simulation)
{
	t_fork	*forks;
	int		i;
	
	i = 0;
	forks = ft_save_malloc(sizeof(t_fork) * simulation->philo_numbers);
	while (i < simulation->philo_numbers)
	{
		forks[i].fork_id = i;
		forks[i].last_picked = -1;
		forks[i].is_picked = NO;
		ft_mutex_handle(&forks[i].mutex, INIT);
		i++;
	}
	simulation->message = ft_save_malloc(sizeof(pthread_mutex_t));
	simulation->stop = ft_save_malloc(sizeof(pthread_mutex_t));
	simulation->death = ft_save_malloc(sizeof(pthread_mutex_t));
	ft_mutex_handle(simulation->message, INIT);
	ft_mutex_handle(simulation->stop, INIT);
	ft_mutex_handle(simulation->death, INIT);
	return (forks);
}
 