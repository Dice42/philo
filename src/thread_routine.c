/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 16:03:22 by mohammoh          #+#    #+#             */
/*   Updated: 2024/05/20 22:11:12 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"



// void	taking_forks_else(t_philo *philo, t_simulation *sim)
// {
// 	t_fork		*forks;

// 	forks = sim->forks;
// 	ft_mutex_handle(&forks[philo->left_fork].mutex, LOCK);
// 	ft_print_message(philo, sim, FORK, forks[philo->left_fork].fork_id);
// 	ft_mutex_handle(&forks[philo->right_fork].mutex, LOCK);
// 	ft_print_message(philo, sim, FORK, forks[philo->left_fork].fork_id);
// }

// void	taking_forks(t_philo *philo, t_simulation *sim)
// {
// 	t_fork		*forks;

// 	forks = sim->forks;
// 	if ((philo->id) % 2 == 0 && philo->id + 1 != sim->philo_numbers)
// 	{
// 		ft_mutex_handle(&forks[philo->right_fork].mutex, LOCK);
// 		ft_print_message(philo, sim, FORK, forks[philo->left_fork].fork_id);
// 		ft_mutex_handle(&forks[philo->left_fork].mutex, LOCK);
// 		ft_print_message(philo, sim, FORK, forks[philo->left_fork].fork_id);
// 	}
// 	else
// 		taking_forks_else(philo, sim);
// }

// void	eating(t_philo *philo, t_simulation *sim)
// {
// 	ft_print_message(philo, philo->simulation, EATING, -1);
// 	philo->eat_counter++;
// 	printf("philo #%d\t eat counter = %d \n", philo->id, philo->eat_counter);
// 	if (philo->eat_counter == philo->max_eat)
// 		ft_print_message(philo, philo->simulation, DONE, -1);
// 	// philo->time_of_last_meal = ft_time();
// 	ft_usleep(sim->time_to_eat);
// 	ft_mutex_handle(&sim->forks[philo->left_fork].mutex, UNLOCK);
// 	ft_mutex_handle(&sim->forks[philo->right_fork].mutex, UNLOCK);
// }

// void	thinking(t_philo *philo)
// {
// 	pthread_mutex_lock(&philo->lock_print);
// 	printf("%ld %d is thinking\n", \
// 		ft_time() - philo->start_time, philo->philo_id + 1);
// 	pthread_mutex_unlock(&philo->lock_print);
// }
