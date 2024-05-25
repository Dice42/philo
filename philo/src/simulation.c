/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 16:52:52 by mohammoh          #+#    #+#             */
/*   Updated: 2024/05/25 14:25:58 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

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
