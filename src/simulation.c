/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 16:52:52 by mohammoh          #+#    #+#             */
/*   Updated: 2024/05/25 13:10:28 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

bool	ft_get_forks2_helper(int f1, int f2, t_philo *ph, t_simulation *sim)
{
	sim->forks[f1].is_picked = YES;
	sim->forks[f1].last_picked = ph->id;
	if (ft_check_death_status(sim))
		return (true);
	ft_print_message(ph, sim, FORK);
	if (f1 == f2)
	{
		ph->is_one = YES;
		return (ft_mutex_handle(&sim->forks[f1].mutex, UNLOCK), true);
	}
	ft_mutex_handle(&sim->forks[f2].mutex, LOCK);
	if (sim->forks[f2].is_picked == NO && sim->forks[f2].last_picked != ph->id)
	{
		sim->forks[f2].is_picked = YES;
		sim->forks[f2].last_picked = ph->id;
		if (ft_check_death_status(sim))
			return (true);
		return (ft_print_message(ph, sim, FORK), true);
	}
	else
	{
		sim->forks[f1].is_picked = NO;
		ft_mutex_handle(&sim->forks[f1].mutex, UNLOCK);
	}
	return (ft_mutex_handle(&sim->forks[f2].mutex, UNLOCK), false);
}

void	ft_get_forks2(int first_fork, int second_fork,
		t_philo *philo, t_simulation *sim)
{
	t_fork	*forks;

	forks = sim->forks;
	while (1)
	{
		if (ft_check_death_status(sim))
			return ;
		ft_mutex_handle(&forks[first_fork].mutex, LOCK);
		if (forks[first_fork].is_picked == NO
			&& forks[first_fork].last_picked != philo->id)
		{
			if (ft_get_forks2_helper(first_fork, second_fork, philo, sim))
				return ;
		}
		else
			ft_mutex_handle(&forks[first_fork].mutex, UNLOCK);
		if (ft_check_death_status(sim))
			return ;
		usleep(50);
	}
}

void	ft_start_simulation(t_philo *philo, t_simulation *simulation)
{
	int	i;

	simulation->start = ft_time();
	simulation->last_meal = ft_save_malloc(sizeof(size_t)
			* simulation->philo_numbers);
	i = -1;
	while (++i < simulation->philo_numbers)
	{
		simulation->last_meal[i] = simulation->start;
		philo[i].simulation = simulation;
	}
	i = -1;
	while (++i < simulation->philo_numbers)
		ft_thread_handle(&simulation->threads[i],
			CREATE, (void *)thread_routine, &philo[i]);
	check_philosopher_deaths(philo);
	i = -1;
	while (++i < simulation->philo_numbers)
		ft_thread_handle(&simulation->threads[i], JOIN, NULL, NULL);
}
