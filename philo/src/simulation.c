/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 16:52:52 by mohammoh          #+#    #+#             */
/*   Updated: 2024/05/26 13:08:54 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/**
 * @brief ill create the philos and also the main thread will continoulsy be 
 * running in a while (1) loop to check if the philos are dead or not
 * before joining 
 * 
 * @param philo 
 * @param simulation 
 */
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
