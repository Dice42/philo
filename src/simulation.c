// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   simulation.c                                       :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/04/24 16:52:52 by mohammoh          #+#    #+#             */
// /*   Updated: 2024/05/09 17:04:12 by mohammoh         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

#include "../includes/philo.h"

// static void	ft_get_even_forks(t_philo *philo, t_simulation *sim)
// {
// 	t_fork		*forks;

// 	forks = sim->forks;
// 	if (forks[philo->right_fork].last_picked != philo->id 
// 		&& forks[philo->left_fork].last_picked != philo->id
// 		&& forks[philo->right_fork].is_picked == NO
// 		&& forks[philo->left_fork].is_picked == NO)
// 	{
// 		forks[philo->right_fork].is_picked = YES;
// 		forks[philo->left_fork].is_picked = YES;
// 		forks[philo->left_fork].last_picked = philo->id;
// 		forks[philo->right_fork].last_picked = philo->id;
// 		ft_mutex_handle(&forks[philo->left_fork].mutex, LOCK);
// 		ft_print_message(philo, sim, FORK, forks[philo->left_fork].fork_id);
// 		printf("lfe: %d\n", philo->left_fork);
// 		ft_mutex_handle(&forks[philo->right_fork].mutex, LOCK);
// 		ft_print_message(philo, sim, FORK, forks[philo->right_fork].fork_id);
// 		printf("rfe: %d\n", philo->right_fork);
// 		philo->has_both_forks = YES;
// 	}
	
// }

static void	ft_get_odd_forks(t_philo *philo, t_simulation *sim)
{
    t_fork *forks;
    int first_fork;
    int second_fork;

    forks = sim->forks;

    // Determine the order of forks to pick up based on philosopher id
   if (philo->id % 2 == 0)
    {
        first_fork = philo->right_fork;
        second_fork = philo->left_fork;

        // Add a slight delay for even philosophers to give odd philosophers a head start
        ft_usleep(50);
    }
    else
    {
        first_fork = philo->left_fork;
        second_fork = philo->right_fork;
    }

    while (1)
    {
        // Lock the first fork
        ft_mutex_handle(&forks[first_fork].mutex, LOCK);
        if (forks[first_fork].is_picked == NO)
        {
            forks[first_fork].is_picked = YES;
            forks[first_fork].last_picked = philo->id;
            ft_print_message(philo, sim, FORK, forks[first_fork].fork_id);

            // Lock the second fork
            ft_mutex_handle(&forks[second_fork].mutex, LOCK);
            if (forks[second_fork].is_picked == NO)
            {
                forks[second_fork].is_picked = YES;
                forks[second_fork].last_picked = philo->id;
                ft_print_message(philo, sim, FORK, forks[second_fork].fork_id);

                // Both forks are successfully picked
                philo->has_both_forks = YES;
                break;
            }
            else
            {
                // Release the first fork if the second fork is not available
                forks[first_fork].is_picked = NO;
                ft_mutex_handle(&forks[first_fork].mutex, UNLOCK);
            }
            ft_mutex_handle(&forks[second_fork].mutex, UNLOCK);
        }
        ft_mutex_handle(&forks[first_fork].mutex, UNLOCK);

        // Sleep for a short duration to avoid busy-waiting
        ft_usleep(50);
    }
}
// static void	sync_threads(t_philo *philo, t_simulation *sim)
// {
// 	ft_mutex_handle(sim->stop, LOCK);
// 	sim->is_ready++;
// 	if (sim->is_ready == sim->philo_numbers)
// 		sim->all_ready = YES;
// 	printf("Philo id %d is ready\n", philo->id);
// 	ft_mutex_handle(sim->stop, UNLOCK);
// 	while (1)
// 	{
// 		ft_mutex_handle(sim->stop, LOCK);
// 		if (sim->all_ready == YES)
// 		{
// 			ft_mutex_handle(sim->stop, UNLOCK);
// 			break;
// 		}
// 		ft_mutex_handle(sim->stop, UNLOCK);
// 		ft_usleep(100);
// 	}
// }
void *thread_routine(void *data)
{
	t_philo			philo;
	t_simulation	*sim;
	
	philo = *(t_philo *)data;
	sim = philo.simulation;

	// sync_threads(&philo, sim);
	printf("Philo id %d is starting simulation\n", philo.id);
	//save the starting time one time 

	ft_mutex_handle(sim->stop, LOCK);
	if (sim->start_flag != 1)
	{
		sim->start = ft_time();
		sim->start_flag = 1;
	}
	ft_mutex_handle(sim->stop, UNLOCK);

	while (1)
	{
		// ft_mutex_handle(sim->stop, LOCK);
		// if (sim->stop_simulation)
		// {
		// 	ft_mutex_handle(sim->stop, UNLOCK);
		// 	break;
		// }
		// ft_mutex_handle(sim->stop, UNLOCK);

		// if (philo.id % 2 != 0)
		//grab forks
		ft_get_odd_forks(&philo, sim);
		// else
		// 	ft_get_even_forks(&philo, sim);
		if (philo.has_both_forks == YES)
			ft_eating(&philo, sim);
		//if he has eaten and his time to die didnt finish
		if (philo.has_eaten == YES && ft_time() - sim->last_meal[philo.id - 1] < sim->time_to_die)
			ft_sleeping(&philo, sim);
		if (philo.has_eaten == YES && ft_time() - sim->last_meal[philo.id - 1] >= sim->time_to_die)
			ft_thinking(&philo, sim);
	}
	return (NULL);
} 

void	ft_start_simulation(t_philo *philo, t_simulation *simulation)
{
	pthread_t death_check_thread;
	int i;

	death_check_thread= ft_save_malloc(sizeof(pthread_t));
	simulation->start = ft_time();
	simulation->last_meal = malloc(sizeof(long long) * simulation->philo_numbers);
	i = -1;
	while (++i < simulation->philo_numbers)
	{
		simulation->last_meal[i] = simulation->start;
		 philo[i].simulation = simulation;
	}
	// ft_thread_handle(&death_check_thread, CREATE, (void *)check_philosopher_deaths, simulation);
	i = -1;
	while (++i < simulation->philo_numbers)
		ft_thread_handle(&simulation->threads[i], CREATE, (void *)thread_routine, &philo[i]);
	i = -1;
	while (++i < simulation->philo_numbers)
		ft_thread_handle(&simulation->threads[i], JOIN, NULL, NULL);
	// ft_thread_handle(&death_check_thread, JOIN, NULL, NULL);
}
