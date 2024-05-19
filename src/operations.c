/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 16:08:42 by mohammoh          #+#    #+#             */
/*   Updated: 2024/05/19 19:27:25 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

//eating
//sleeping
//thinking
//monitor if dead :if the philosopher is not eating or thinking and the timeing for eating is finsihed 


/* Monitioring */

// bool	ft_isdead(t_philo philo, t_simulation *sim)
// {
// 	//if the philospher is not eating or thinking and the time for eating has finished
// 	//kill the philospher
// 	return (true);
// }
// {
// 	//if the philospher is not eating or thinking and the time for eating has finished
// 	//kill the philospher
// 	return (true);
// }

void	ft_eating(t_philo *philo, t_simulation *sim)
{
	// pick up the seconed fork 
	
	//the fork could be taken by the other philospher
	if (sim->forks[philo->right_fork].is_taken == NO && sim->forks[philo->left_fork].is_taken == YES)
	{
		ft_mutex_handle(&sim->forks[philo->right_fork].mutex, LOCK);
		sim->forks[philo->right_fork].is_taken = YES;
		ft_print_message(philo, philo->simulation, FORK, sim->forks[philo->right_fork].fork_id);
		if (philo->eat_counter < philo->max_eat)
		{	
			ft_print_message(philo, philo->simulation, EATING, -1);
			philo->eat_counter++;
			usleep(sim->time_to_eat);
			printf("philo #%d\t eat counter = %d \n", philo->id, philo->eat_counter);
			if (philo->eat_counter == philo->max_eat)
			{
				ft_print_message(philo, philo->simulation, DONE, -1);
				// need to have an exit function to free we need to send a signal to the simulation to kill all philosophoers and free and destroy all the mutexes
			}
		}
		if (sim->forks[philo->right_fork].is_taken == YES && sim->forks[philo->left_fork].is_taken == YES)
		{
			ft_mutex_handle(&sim->forks[philo->right_fork].mutex, UNLOCK);
			ft_mutex_handle(&sim->forks[philo->left_fork].mutex, UNLOCK);
			sim->forks[philo->left_fork].is_taken = NO;
			sim->forks[philo->right_fork].is_taken = NO;
		}
	}
}

void	ft_sleeping(t_philo *philo, t_simulation *sim)
{
	ft_print_message(philo, sim, SLEEPING, -1);
	usleep(sim->time_to_sleep);
}


// i need to make a monitor thread to check the time if a philosopher is not eating or thinking and the time for eating has finished


// time to eat + time to sleep should be less than time to die 