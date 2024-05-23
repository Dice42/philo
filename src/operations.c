/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 16:08:42 by mohammoh          #+#    #+#             */
/*   Updated: 2024/05/23 20:50:32 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void check_philosopher_deaths(t_simulation *sim)
{
	int i;
	size_t current_time;

	i = -1;
	while (1)
	{
		i = -1;
		ft_mutex_handle(sim->stop, LOCK);
		while (++i < sim->philo_numbers) 
		{
			current_time = ft_time();
			if (current_time - sim->last_meal[i] > sim->time_to_die)
			{
				sim->stop_simulation = 1;
				printf("Philo id %d is dead\n", i);
				exit(1);
				ft_mutex_handle(sim->death, UNLOCK);
				return;
			}
		}
		ft_mutex_handle(sim->stop, UNLOCK);
		ft_usleep(100); 
	}
}



void	ft_eating(t_philo *philo, t_simulation *sim)
{
	if (philo->eat_counter < philo->max_eat)
	{	
		ft_print_message(philo, philo->simulation, EATING, -42);
		sim->last_meal[philo->id - 1] = ft_time();
		ft_usleep(sim->time_to_eat); 
		philo->eat_counter++;
		printf("philo #%d\t eat counter = %d \n", philo->id, philo->eat_counter);
		if (philo->eat_counter == philo->max_eat)
		{
			// exit and unlock all forks
			ft_print_message(philo, philo->simulation, DONE, -42);
		}
		philo->has_eaten = YES;
		sim->forks[philo->right_fork].is_picked = NO;
		sim->forks[philo->left_fork].is_picked = NO;
		ft_mutex_handle(&sim->forks[philo->right_fork].mutex, UNLOCK);
		ft_mutex_handle(&sim->forks[philo->left_fork].mutex, UNLOCK);
		// ft_mutex_handle(sim->stop, LOCK);  // Ensure thread-safe access to shared data
		// ft_mutex_handle(sim->stop, UNLOCK);
		philo->has_both_forks = NO;
	}
}
// void ft_eating(t_philo *philo, t_simulation *sim)
// {
//     t_fork *forks;

//     forks = sim->forks;

//     if (philo->eat_counter < philo->max_eat)
//     {
//         ft_print_message(philo, philo->simulation, EATING, -42);
//         sim->last_meal[philo->id - 1] = ft_time();
//         ft_usleep(sim->time_to_eat);
//         philo->eat_counter++;

//         // Check if the philosopher has eaten the maximum number of times
//         if (philo->eat_counter == philo->max_eat)
//         {
//             ft_print_message(philo, philo->simulation, DONE, -42);
//         }

//         // Mark the philosopher as having eaten
//         philo->has_eaten = YES;

//         // Release both forks and unlock their mutexes
//         // ft_mutex_handle(&forks[philo->left_fork].mutex, LOCK);
//         forks[philo->left_fork].is_picked = NO;
//         ft_mutex_handle(&forks[philo->left_fork].mutex, UNLOCK);

//         // ft_mutex_handle(&forks[philo->right_fork].mutex, LOCK);
//         forks[philo->right_fork].is_picked = NO;
//         ft_mutex_handle(&forks[philo->right_fork].mutex, UNLOCK);

//         // Mark that the philosopher no longer has both forks
//         philo->has_both_forks = NO;
//     }
// }

void	ft_sleeping(t_philo *philo, t_simulation *sim)
{
	ft_print_message(philo, sim, SLEEPING, -42);
	ft_usleep(sim->time_to_sleep);
	philo->has_eaten = NO;
}

void	ft_thinking(t_philo *philo, t_simulation *sim)
{
	ft_print_message(philo, sim, THINKING, -42);
}