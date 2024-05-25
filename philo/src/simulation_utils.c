/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 12:36:42 by mohammoh          #+#    #+#             */
/*   Updated: 2024/05/25 20:37:00 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*thread_routine(void *data)
{
	t_philo			philo;
	t_simulation	*sim;

	philo = *(t_philo *)data;
	sim = philo.simulation;
	get_start_time(sim);
	while (1)
	{
		if (!ft_check_death_status(sim))
			ft_get_forks(&philo, sim);
		if (ft_check_death_status(sim))
			return (NULL);
		if (!ft_check_death_status(sim) && !philo.is_one)
			ft_eating(&philo);
		if (ft_check_death_status(sim))
			return (NULL);
		if (philo.has_eaten == YES
			&& !ft_check_death_status(sim) && !philo.is_one)
			ft_sleeping(&philo);
		if (ft_check_death_status(sim))
			return (NULL);
		if (!ft_check_death_status(sim) && !philo.is_one)
			ft_thinking(&philo);
	}
	return (NULL);
}

void	get_start_time(t_simulation *sim)
{
	ft_mutex_handle(sim->stop, LOCK);
	if (sim->start_flag != 1)
	{
		sim->start = ft_time();
		sim->start_flag = 1;
	}
	ft_mutex_handle(sim->stop, UNLOCK);
}

int	ft_check_death_status(t_simulation *sim)
{
	ft_mutex_handle(sim->done, LOCK);
	if (sim->stop_simulation == 1 || sim->all_done == sim->philo_numbers)
	{
		ft_mutex_handle(sim->done, UNLOCK);
		return (1);
	}
	ft_mutex_handle(sim->done, UNLOCK);
	return (0);
}
