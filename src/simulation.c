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

int		ft_check_death_status(t_simulation *sim)
{
	ft_mutex_handle(sim->stop, LOCK);
	if (sim->stop_simulation == 1 || sim->stop_simulation == 2)
	{
		ft_mutex_handle(sim->stop, UNLOCK);
			return (1);
	}
	ft_mutex_handle(sim->stop, UNLOCK);
	return (0);
}

static void ft_get_forks2(int first_fork, int second_fork, t_philo *philo, t_simulation *sim)
{
	t_fork		*forks;

	forks = sim->forks;
	while (1)
	{
		if(ft_check_death_status(sim))
			return ;
		ft_mutex_handle(&forks[first_fork].mutex, LOCK);
		if (forks[first_fork].is_picked == NO 
			&& forks[first_fork].last_picked != philo->id)
		{
			forks[first_fork].is_picked = YES;
			forks[first_fork].last_picked = philo->id;
			ft_print_message(philo, sim, FORK);
			if (first_fork != second_fork)
			{
				ft_mutex_handle(&forks[second_fork].mutex, LOCK);
				if (forks[second_fork].is_picked == NO
					&& forks[second_fork].last_picked != philo->id)
				{
					forks[second_fork].is_picked = YES;
					forks[second_fork].last_picked = philo->id;
					ft_print_message(philo, sim, FORK);
					break;
				}
				else
				{
					forks[first_fork].is_picked = NO;
					ft_mutex_handle(&forks[first_fork].mutex, UNLOCK);
				}
			}
			if (first_fork != second_fork)
				ft_mutex_handle(&forks[second_fork].mutex, UNLOCK);
		}
		else
			ft_mutex_handle(&forks[first_fork].mutex, UNLOCK);
		usleep(50);
	}
}
static void	ft_get_forks(t_philo *philo, t_simulation *sim)
{
	int			first_fork;
	int			second_fork;

	if (philo->id % 2 != 0)
	{
		first_fork = philo->right_fork;
		second_fork = philo->left_fork;
	}
	else
	{
		first_fork = philo->left_fork;
		second_fork = philo->right_fork;
		usleep(10);
	}
	ft_get_forks2(first_fork, second_fork, philo, sim);
}
static void get_start_time(t_simulation *sim)
{
	ft_mutex_handle(sim->stop, LOCK);
	if (sim->start_flag != 1)
	{
		sim->start = ft_time();
		sim->start_flag = 1;
	}
	ft_mutex_handle(sim->stop, UNLOCK);
}
void *thread_routine(void *data)
{
	t_philo			philo;
	t_simulation	*sim;

	philo = *(t_philo *)data;
	sim = philo.simulation;
	get_start_time(sim);
	ft_mutex_handle(sim->stop, UNLOCK);
	while (1)
	{
		if (!ft_check_death_status(sim))
			ft_get_forks(&philo, sim);
		if (ft_check_death_status(sim))
			return (NULL);
		if (!ft_check_death_status(sim))
			ft_eating(&philo);
		if (philo.has_eaten == YES && !ft_check_death_status(sim))
			ft_sleeping(&philo);
		if (ft_check_death_status(sim))
			return (NULL);
		if (!ft_check_death_status(sim))
			ft_thinking(&philo);
		if (ft_check_death_status(sim))
			return (NULL);
	}
	return (NULL);
} 

void	ft_start_simulation(t_philo *philo, t_simulation *simulation)
{
	int	i;

	simulation->start = ft_time();
	simulation->last_meal = ft_save_malloc(sizeof(size_t) * simulation->philo_numbers);
	i = -1;
	while (++i < simulation->philo_numbers)
	{
		simulation->last_meal[i] = simulation->start;
		philo[i].simulation = simulation;
	}
	i = -1;
	while (++i < simulation->philo_numbers)
		ft_thread_handle(&simulation->threads[i], CREATE, (void *)thread_routine, &philo[i]);
	check_philosopher_deaths(philo);
	i = -1;
	while (++i < simulation->philo_numbers)
		ft_thread_handle(&simulation->threads[i], JOIN, NULL, NULL);
}
