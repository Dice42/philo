/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 21:06:46 by mohammoh          #+#    #+#             */
/*   Updated: 2024/05/26 13:11:18 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/**
 * @brief check if the philosopher is dead or all the philosophers 
 * are done eating. im call this function regulary everywhere
 * @param sim 
 * @return 1 if dead or done 0 if not
 */
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

/**
 * @brief this is my monitor function that checks if the philosopher
 * dies or all the philosophers are done eating
 * @param data contains the philosopher structure
 */
void	check_philosopher_deaths(void *data)
{
	t_philo			*philo;
	t_simulation	*sm;
	int				i;

	philo = (t_philo *)data;
	sm = philo->simulation;
	while (1)
	{
		i = -1;
		ft_mutex_handle(sm->done, LOCK);
		while (++i < sm->philo_numbers)
		{
			if (sm->stop_simulation == 1 || sm->all_done == sm->philo_numbers)
				return (usleep(500), ft_mutex_handle(sm->done, UNLOCK));
			if (ft_time() - sm->last_meal[i] >= sm->time_to_die)
			{
				ft_print_message(&philo[i], sm, DIED);
				ft_mutex_handle(sm->done, UNLOCK);
				return ;
			}
		}
		ft_mutex_handle(sm->done, UNLOCK);
	}
}
