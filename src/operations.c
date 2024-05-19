/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 16:08:42 by mohammoh          #+#    #+#             */
/*   Updated: 2024/05/19 16:54:41 by mohammoh         ###   ########.fr       */
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
	printf("before incrementing : philo #%d\t eat counter = %d \n", philo->id, philo->eat_counter);
	if (sim->forks[philo->right_fork].is_taken == NO && sim->forks[philo->left_fork].is_taken == YES)
	{
		ft_mutex_handle(&sim->forks[philo->right_fork].mutex, LOCK);
		sim->forks[philo->right_fork].is_taken = YES;
		ft_print_message(philo, philo->simulation, FORK, sim->forks[philo->right_fork].fork_id);
		if (philo->eat_counter <= philo->max_eat)
		{	
			ft_print_message(philo, philo->simulation, EATING, -1);
			philo->eat_counter++;
			
			printf("philo #%d\t eat counter = %d \n", philo->id, philo->eat_counter);
		}
		else if (philo->eat_counter == philo->max_eat)
		{
			ft_print_message(philo, philo->simulation, DONE, -1);
			exit(0); // need to have an exit function to free
		}
		if (sim->forks[philo->right_fork].is_taken == YES && sim->forks[philo->left_fork].is_taken == YES)
		{
			ft_mutex_handle(&sim->forks[philo->right_fork].mutex, UNLOCK);
			ft_mutex_handle(&sim->forks[philo->left_fork].mutex, UNLOCK);
			sim->forks[philo->left_fork].is_taken = NO;
			sim->forks[philo->right_fork].is_taken = NO;
		}
		printf("after leaving philo #%d\t eat counter = %d \n", philo->id, philo->eat_counter);
	}

	// sleep (100); 
	// else
	// 	// start thinking
	
		//return
	// ft_print_message(&philo, philo.simulation, EATING);
	//if the philosopher has the two forks it means you can it start eating 
	//print the message that the philospher is eating
	//unlock the two forks
	//increase the eating counter
	//sleep for the time to eat
}

// void	ft_sleeping(t_philo philo, t_simulation *sim)
// {
// 	//print the message that the philospher is sleeping
// 	//sleep for the time to sleep
// }

// void	ft_thinking(t_philo philo, t_simulation *sim)
// {
// 	//print the message that the philospher is thinking
// }