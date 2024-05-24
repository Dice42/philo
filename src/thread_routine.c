/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 16:59:37 by mohammoh          #+#    #+#             */
/*   Updated: 2024/05/24 18:46:36 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_free(t_simulation *sim, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < sim->philo_numbers)
	{
		ft_mutex_handle(&sim->forks[i].mutex, DESTROY);
		i++;
	}
	free(sim->last_meal);
	free(sim->forks);
	free(sim->threads);
	free(philo);
	free(sim->message);
	free(sim->stop);
	free(sim->death);
	
}