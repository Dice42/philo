/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 18:03:47 by mohammoh          #+#    #+#             */
/*   Updated: 2024/05/25 01:13:46 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

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
		if (sim->stop_simulation == 1 || sim->stop_simulation == 2)
			return ;
		usleep(500);
	}
}
