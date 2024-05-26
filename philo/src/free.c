/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 16:59:37 by mohammoh          #+#    #+#             */
/*   Updated: 2024/05/26 11:24:36 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/**
 * @brief this function frees all the memory that was allocated
 * @param sim contains the simulation structure
 */
void	ft_free(t_simulation *sim)
{
	int	i;

	i = 0;
	while (i < sim->philo_numbers)
	{
		pthread_mutex_destroy(&sim->forks[i].mutex);
		i++;
	}
	pthread_mutex_destroy(sim->message);
	pthread_mutex_destroy(sim->stop);
	pthread_mutex_destroy(sim->done);
	free(sim->last_meal);
	free(sim->message);
	free(sim->stop);
	free(sim->done);
	free(sim->threads);
	free(sim->forks);
}
