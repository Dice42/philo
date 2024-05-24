/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 21:06:46 by mohammoh          #+#    #+#             */
/*   Updated: 2024/05/25 01:31:40 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	check_philosopher_deaths(void *data)
{
	t_philo			*philo;
	t_simulation	*sim;
	int				i;

	philo = (t_philo *)data;
	sim = philo->simulation;
	while (1)
	{
		i = -1;
		ft_mutex_handle(sim->death, LOCK);
		while (++i < sim->philo_numbers)
		{
			if (sim->stop_simulation == 1 || sim->stop_simulation == 2)
			{
				ft_mutex_handle(sim->death, UNLOCK);
				return ;
			}
			if (ft_time() - sim->last_meal[i] >= sim->time_to_die)
			{
				ft_print_message(&philo[i], sim, DIED);
				ft_mutex_handle(sim->death, UNLOCK);
				return ;
			}
		}
		ft_mutex_handle(sim->death, UNLOCK);
	}
}
