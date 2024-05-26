/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_fork.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 12:39:00 by mohammoh          #+#    #+#             */
/*   Updated: 2024/05/26 11:32:58 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static bool	ft_get_forks2_utils(int f1, int f2, t_philo *ph, t_simulation *sim)
{
	sim->forks[f1].is_picked = YES;
	sim->forks[f1].last_picked = ph->id;
	if (ft_check_death_status(sim))
		return (ft_mutex_handle(&sim->forks[f1].mutex, UNLOCK), true);
	ft_print_message(ph, sim, FORK);
	if (ft_check_death_status(sim))
		return (ft_mutex_handle(&sim->forks[f1].mutex, UNLOCK), true);
	if (f1 == f2)
	{
		ph->is_one = YES;
		return (ft_mutex_handle(&sim->forks[f1].mutex, UNLOCK), true);
	}
	if (ft_check_death_status(sim))
		return (ft_mutex_handle(&sim->forks[f1].mutex, UNLOCK), true);
	ft_mutex_handle(&sim->forks[f2].mutex, LOCK);
	if (ft_check_death_status(sim))
	{
		ft_mutex_handle(&sim->forks[f1].mutex, UNLOCK);
		ft_mutex_handle(&sim->forks[f2].mutex, UNLOCK);
		return (true);
	}
	return (false);
}

static bool	ft_get_forks2_helper(int f1, int f2, t_philo *ph, t_simulation *sim)
{
	if (ft_get_forks2_utils(f1, f2, ph, sim))
		return (true);
	if (sim->forks[f2].is_picked == NO && sim->forks[f2].last_picked != ph->id)
	{
		sim->forks[f2].is_picked = YES;
		sim->forks[f2].last_picked = ph->id;
		if (ft_check_death_status(sim))
		{
			ft_mutex_handle(&sim->forks[f1].mutex, UNLOCK);
			ft_mutex_handle(&sim->forks[f2].mutex, UNLOCK);
			return (true);
		}
		return (ft_print_message(ph, sim, FORK), true);
	}
	else
	{
		sim->forks[f1].is_picked = NO;
		ft_mutex_handle(&sim->forks[f1].mutex, UNLOCK);
	}
	return (ft_mutex_handle(&sim->forks[f2].mutex, UNLOCK), false);
}

static void	ft_get_forks2(int first_fork, int second_fork,
		t_philo *philo, t_simulation *sim)
{
	t_fork	*forks;

	forks = sim->forks;
	while (1)
	{
		if (ft_check_death_status(sim))
			return ;
		ft_mutex_handle(&forks[first_fork].mutex, LOCK);
		if (forks[first_fork].is_picked == NO && forks[first_fork].last_picked
			!= philo->id && !ft_check_death_status(sim))
		{
			if (ft_check_death_status(sim))
				return (ft_mutex_handle(&forks[first_fork].mutex, UNLOCK));
			if (ft_get_forks2_helper(first_fork, second_fork, philo, sim))
				return ;
		}
		else
			ft_mutex_handle(&forks[first_fork].mutex, UNLOCK);
		usleep(50);
	}
}

/**
 * @brief getting forks for the philosopher by letting the odd philos to pick
 * the right fork first and the even philos to pick the left fork first and
 * ill give a head start for the odds
 * @param philo 
 * @param sim 
 */
void	ft_get_forks(t_philo *philo, t_simulation *sim)
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
		usleep(20);
	}
	if (ft_check_death_status(sim))
		return ;
	ft_get_forks2(first_fork, second_fork, philo, sim);
}
