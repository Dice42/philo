/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 18:03:47 by mohammoh          #+#    #+#             */
/*   Updated: 2024/05/26 13:04:22 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

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

size_t	ft_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	ft_usleep(size_t ms, t_simulation *sim)
{
	size_t	start;

	start = ft_time();
	while ((ft_time() - start) < ms)
	{
		ft_mutex_handle(sim->done, LOCK);
		if (sim->stop_simulation == 1 || sim->all_done == sim->philo_numbers)
		{
			ft_mutex_handle(sim->done, UNLOCK);
			return ;
		}
		ft_mutex_handle(sim->done, UNLOCK);
		usleep(500);
	}
}
