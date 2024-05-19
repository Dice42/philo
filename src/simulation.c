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

	printf("\n\n\n philo number [%d]  in the simulation process\n\n\n", philo.id);
	while (1)
	{
		//&& philo.left_fork != philo.right_fork for only one philo
		if (philo.id % 2 != 0)
		{
			printf("from simuylation  #%d\t eat counter = %d \n", philo.id, philo.eat_counter);
			if (sim->forks[philo.left_fork].is_taken == NO)
			{
				ft_mutex_handle(&sim->forks[philo.left_fork].mutex, LOCK);
				sim->forks[philo.left_fork].is_taken = YES;
				ft_print_message(&philo, sim, FORK,sim->forks[philo.left_fork].fork_id);
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
			ft_eating(&philo, sim);
	}

	// // if (philo.id % 2 == 0 && philo.left_fork != philo.right_fork && sim->forks[philo.left_fork].is_taken == NO)
	// else if (philo.id / 2 == 0 && philo.left_fork != philo.right_fork && sim->forks[philo.left_fork].is_taken == YES)
	// {
	// 	ft_mutex_handle(&sim->forks[philo.left_fork].mutex, LOCK);
	// 	ft_print_message(&philo, sim, FORK);
	// }
	// else if (philo.id / 2 != 0 && philo.left_fork != philo.right_fork && sim->forks[philo.left_fork].is_taken == NO)
	// {
	// 	ft_mutex_handle(&sim->forks[philo.left_fork].mutex, LOCK);
	// 	sim->forks[philo.left_fork].is_taken = YES;
	// 	ft_print_message(&philo, sim, FORK);
	// 	// printf("philo id %d\t fork id %d\n",philo.id, sim->forks[philo.left_fork].fork_id); // we need to have some sort of a flag to check if the fork is available
	// }
	// else
	// {
	// 	ft_mutex_handle(&sim->forks[philo.left_fork].mutex, LOCK);
	// 	ft_print_message(&philo, sim, FORK);
	// }
	// 	// printf("philo id %d\t fork id %d\n",philo.id, sim->forks[philo.left_fork].fork_id); // we need to have some sort of a flag to check if the fork is available
	// // while (1)
	// // {
	// // 	// if (philo.is_dead || philo.eat_counter >= sim->max_eat)  
	// // 	// {
	// // 	// 	ft_mutex_handle(sim->stop, LOCK);
	// // 	// 	break;
	// // 	// }
	// // 	//lock right fork if available
	// // 	if (philo.id % 2 == 0)
	// // 	{
	// // 		printf("sleeping");
	// // 		usleep(1000); //sleep until the odds philos finish eating
	// // 		//sleep until the odds philos finish eating
	// // 	}
	// // 	// ft_print_message(&philo, sim, FORK);
	// // 	// ft_eating(&philo);
	// // 	// ft_sleeping(&philo);
	// // 	// ft_thinking(&philo);
	// // }
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
	//4-sychronize the beginning of the simulation
	//4.1 - create a mutex for each philosopher
	//4.2 - create a mutex for each fork
	//4.3 - create a mutex for the message
	//4.4 - create a mutex for the death
	//4.5 - create a mutex for the stop
	//5- start the simulation
	//6- join all threads
	//	free all memory 
	
	int i;
	

	i = -1;
	while (++i < simulation->philo_numbers)
		philo[i].simulation = simulation;
	i = -1;
	while (++i < simulation->philo_numbers)
		ft_thread_handle(&simulation->threads[i], CREATE, (void *)thread_routine, &philo[i]);
	// i = -1;
	while (++i < simulation->philo_numbers)
		ft_thread_handle(&simulation->threads[i], JOIN, NULL, NULL);
}