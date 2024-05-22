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

static void	ft_get_even_forks(t_philo *philo, t_simulation *sim)
{
	t_fork		*forks;

	forks = sim->forks;
	ft_mutex_handle(&forks[philo->left_fork].mutex, LOCK);
	ft_print_message(philo, sim, FORK, forks[philo->left_fork].fork_id);
	forks[philo->left_fork].last_picked = philo->id;
	ft_mutex_handle(&forks[philo->right_fork].mutex, LOCK);
	ft_print_message(philo, sim, FORK, forks[philo->right_fork].fork_id);
	forks[philo->right_fork].last_picked = philo->id;
}

static void	ft_get_odd_forks(t_philo *philo, t_simulation *sim)
{
	t_fork		*forks;

	forks = sim->forks;
	if ((philo->id) % 2 == 0 && forks[philo->right_fork].last_picked != philo->id 
		&& forks[philo->left_fork].last_picked != philo->id)
	{
		ft_mutex_handle(&forks[philo->right_fork].mutex, LOCK);
		ft_print_message(philo, sim, FORK, forks[philo->right_fork].fork_id);
		forks[philo->right_fork].last_picked = philo->id;
		ft_mutex_handle(&forks[philo->left_fork].mutex, LOCK);
		ft_print_message(philo, sim, FORK, forks[philo->left_fork].fork_id);
		forks[philo->left_fork].last_picked = philo->id;
	}
	else
		ft_get_even_forks(philo, sim);
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
	printf("Philo id %d is starting simulation\n", phimlo.id);

	while (1)
	{
		ft_mutex_handle(sim->stop, LOCK);
		if (sim->stop_simulation)
		{
			ft_mutex_handle(sim->stop, UNLOCK);
			break;
		}
		ft_mutex_handle(sim->stop, UNLOCK);
		if (philo.id % 2 != 0)
			ft_get_odd_forks(&philo, sim);
		// else
		// 	ft_get_even_forks(&philo, sim);
		ft_eating(&philo, sim);
		ft_sleeping(&philo, sim);
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
	ft_thread_handle(&death_check_thread, CREATE, (void *)check_philosopher_deaths, simulation);
	i = -1;
	while (++i < simulation->philo_numbers)
		ft_thread_handle(&simulation->threads[i], CREATE, (void *)thread_routine, &philo[i]);
	i = -1;
	while (++i < simulation->philo_numbers)
		ft_thread_handle(&simulation->threads[i], JOIN, NULL, NULL);
	ft_thread_handle(&death_check_thread, JOIN, NULL, NULL);
}
