/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 21:06:46 by mohammoh          #+#    #+#             */
/*   Updated: 2024/05/24 23:17:42 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	check_philosopher_deaths(void *data)
{
	t_simulation	*sim;
	t_philo			*philo;
	size_t			diff_time;
	int				i;
	
	philo = (t_philo *)data;
	sim = philo->simulation;
	while (1)
	{
		i = -1;
		ft_mutex_handle(sim->death, LOCK); 
		while (++i < sim->philo_numbers) 
		{	
			diff_time = ft_time() - sim->last_meal[i];
			if (sim->stop_simulation == 1 || sim->stop_simulation == 2)
			{
				ft_mutex_handle(sim->death, UNLOCK);
				return ;
			}
			if (diff_time >= sim->time_to_die)
			{
				ft_print_message(&philo[i], sim, DIED);
				ft_mutex_handle(sim->death, UNLOCK);
				return ;
			}
		}
		ft_mutex_handle(sim->death, UNLOCK);
	}
}
