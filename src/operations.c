/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 16:08:42 by mohammoh          #+#    #+#             */
/*   Updated: 2024/05/22 16:07:57 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void check_philosopher_deaths(t_simulation *sim)
{
	int i;
	long long current_time;

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
		ft_usleep(sim->time_to_eat); 
		ft_print_message(philo, philo->simulation, EATING, -42);
		philo->eat_counter++;
		ft_mutex_handle(sim->stop, LOCK);  // Ensure thread-safe access to shared data
		sim->last_meal[philo->id - 1] = ft_time();
		ft_mutex_handle(sim->stop, UNLOCK);
		printf("philo #%d\t eat counter = %d \n", philo->id, philo->eat_counter);
		if (philo->eat_counter == philo->max_eat)
		{
			ft_print_message(philo, philo->simulation, DONE, -42);
		}
		ft_mutex_handle(&sim->forks[philo->right_fork].mutex, UNLOCK);
		ft_mutex_handle(&sim->forks[philo->left_fork].mutex, UNLOCK);
	}
}

void	ft_sleeping(t_philo *philo, t_simulation *sim)
{
	ft_print_message(philo, sim, SLEEPING, -42);
	usleep(sim->time_to_sleep);
}

void	ft_thinking(t_philo *philo, t_simulation *sim)
{
	ft_print_message(philo, sim, THINKING, -42);
	usleep(sim->time_to_sleep);
}