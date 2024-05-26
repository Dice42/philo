/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 12:36:42 by mohammoh          #+#    #+#             */
/*   Updated: 2024/05/26 13:07:25 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
/**
 * @brief the routine where all the majic happenes
 * ill get the first philosopher starts will get the the starting time
 * @param data 
 * @return void* 
 */
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
