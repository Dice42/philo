/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 16:08:42 by mohammoh          #+#    #+#             */
/*   Updated: 2024/05/18 17:02:34 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//eating
//sleeping
//thinking
//monitor if dead :if the philosopher is not eating or thinking and the timeing for eating is finsihed 


/* Monitioring */

bool	ft_isdead(t_philo philo, t_simulation *sim)
{
	//if the philospher is not eating or thinking and the time for eating has finished
	//kill the philospher
	return (true);
}
{
	//if the philospher is not eating or thinking and the time for eating has finished
	//kill the philospher
	return (true);
}

void	ft_eating(t_philo philo, t_simulation *sim)
{
	// pick up the seconed fork 
	
	if (sim->forks[philo.right_fork].is_taken == NO)
	{
		ft_mutex_handle(&philo.simulation->forks[philo.right_fork].mutex, LOCK);
		philo.simulation->forks[philo.right_fork].is_taken = YES;
		ft_print_message(&philo, philo.simulation, FORK);
		if (philo.eat_counter != philo.max_eat)
		{	
			ft_print_message(&philo, philo.simulation, EATING);
			philo.eat_counter++;
		}
		else if (philo.eat_counter == philo.max_eat)
		{
			ft_print_message(&philo, philo.simulation, DONE);
			exit(0); // need to have an exit function
		}
	}
		//unlock the first fork
		//unlock the second fork
		//return
	ft_print_message(&philo, philo.simulation, EATING);
	//if the philosopher has the two forks it means you can it start eating 
	//print the message that the philospher is eating
	//unlock the two forks
	//increase the eating counter
	//sleep for the time to eat
}

void	ft_sleeping(t_philo philo, t_simulation *sim)
{
	//print the message that the philospher is sleeping
	//sleep for the time to sleep
}

void	ft_thinking(t_philo philo, t_simulation *sim)
{
	//print the message that the philospher is thinking
}