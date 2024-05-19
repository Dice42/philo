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


void *thread_routine(void *data)
{
	t_philo			philo;
	t_simulation	*sim;
	
	philo = *(t_philo *)data;
	sim = philo.simulation;

	printf("philo %d\n", philo.id);

	// exit(1);
	// printf("all ready %d # philo, starting simulation\n", sim->is_ready);
	// exit(1);
	// printf("philo id %d entered the simulation\n", philo.id);
	while (1)
	{

		//first i need to sychronize all the philos to start eating at the same time

		// wait_for_all(sim);
		//&& philo.left_fork != philo.right_fork for only one philo
		if (philo.id % 2 != 0)
		{
			if (sim->forks[philo.left_fork].is_taken == NO)
			{
				ft_mutex_handle(&sim->forks[philo.left_fork].mutex, LOCK);
				sim->forks[philo.left_fork].is_taken = YES;
				ft_print_message(&philo, sim, FORK, sim->forks[philo.left_fork].fork_id);
			}
			// printf("philo id %d\t fork id %d\n",philo.id, sim->forks[philo.left_fork].fork_id); // we need to have some sort of a flag to check if the fork is available
		}
		// else if (philo.id % 2 == 0)
		// 	{
		// 		printf("sleeping %d\n", philo.id);
		// 		sleep(100000); //sleep until the odds philos finish eating
		// 		if (sim->forks[philo.left_fork].is_taken == NO)
		// 		{
		// 			ft_mutex_handle(&sim->forks[philo.left_fork].mutex, LOCK);
		// 			sim->forks[philo.left_fork].is_taken = YES;
		// 			ft_print_message(&philo, sim, FORK, sim->forks[philo.left_fork].fork_id);
		// 		}
		// 	}
		if (philo.id % 2 != 0)
		{
			ft_eating(&philo, sim);
			//need to check if the philosopher is done eating to stop the simulation
			// time to eat + time to sleep should be less than time to die 
			ft_sleeping(&philo, sim);
			ft_print_message(&philo, sim, THINKING, -1);
		}
	}

	return (NULL);
}

long long ft_get_time(void)
{
	struct timeval time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	ft_start_simulation(t_philo *philo, t_simulation *simulation)
{
	// unsigned int start_time;
	simulation->start = ft_get_time();
	// printf("starting time = [%lld]\n", simulation->start);
	
	//1-if only one philosopher //should die after he's sleeping time and thinking time finishes
	//3-create a monitor thread -> searching for dead philosophers
	//4-create a monitor thread -> searching for philosophers that have eaten the max number of times
	int i;
	

	i = -1;
	while (++i < simulation->philo_numbers)
		philo[i].simulation = simulation;
	i = -1;
	while (++i < simulation->philo_numbers)
		ft_thread_handle(&simulation->threads[i], CREATE, (void *)thread_routine, &philo[i]);
	i = -1;
	while (++i < simulation->philo_numbers)
		ft_thread_handle(&simulation->threads[i], JOIN, NULL, NULL);
}

