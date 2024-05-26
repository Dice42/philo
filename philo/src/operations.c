/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 16:08:42 by mohammoh          #+#    #+#             */
/*   Updated: 2024/05/26 13:01:23 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/**
 * @brief philo starts eating here updating the time of the last meal 
 * also incrementing the eat counter and an integer if it finishes 
 * the required meal, note that a philo wont stop eating if finishes 
 * the required meal eating
 * itll only will stop when all the philos finish their
 * and lastly ill unlock the forks before sleeping
 * @param philo 
 */
void	ft_eating(t_philo *philo)
{
	t_simulation	*sim;

	sim = philo->simulation;
	ft_print_message(philo, philo->simulation, EATING);
	ft_mutex_handle(sim->done, LOCK);
	sim->last_meal[philo->id - 1] = ft_time();
	ft_mutex_handle(sim->done, UNLOCK);
	ft_usleep(sim->time_to_eat, sim); 
	philo->eat_counter++;
	if (philo->eat_counter == philo->max_eat)
	{
		ft_mutex_handle(sim->done, LOCK);
		sim->all_done++;
		ft_mutex_handle(sim->done, UNLOCK);
		ft_print_message(philo, philo->simulation, DONE);
	}
	philo->has_eaten = YES;
	sim->forks[philo->right_fork].is_picked = NO;
	sim->forks[philo->left_fork].is_picked = NO;
	ft_mutex_handle(&sim->forks[philo->right_fork].mutex, UNLOCK);
	ft_mutex_handle(&sim->forks[philo->left_fork].mutex, UNLOCK);
}

/**
 * @brief philo starts sleeping with required time to sleep
 * @param philo 
 */
void	ft_sleeping(t_philo *philo)
{
	ft_print_message(philo, philo->simulation, SLEEPING);
	ft_usleep(philo->simulation->time_to_sleep, philo->simulation);
	philo->has_eaten = NO;
}

void	ft_thinking(t_philo *philo)
{
	ft_print_message(philo, philo->simulation, THINKING);
}
