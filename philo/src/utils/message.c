/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 01:19:24 by mohammoh          #+#    #+#             */
/*   Updated: 2024/05/25 20:11:27 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

static char	*ft_message(int opcode)
{
	if (opcode == FORK)
		return ("has taken a fork");
	else if (opcode == EATING)
		return ("is eating");
	else if (opcode == SLEEPING)
		return ("is sleeping");
	else if (opcode == THINKING)
		return ("is thinking");
	else if (opcode == DIED)
		return ("died");
	else if (opcode == DONE)
		return ("done");
	return (NULL);
}

void	ft_print_message(t_philo *philo, t_simulation *simulation, int opcode)
{
	ft_mutex_handle(simulation->message, LOCK);
	if (opcode == DIED)
	{
		ft_mutex_handle(simulation->stop, LOCK);
		simulation->stop_simulation = 1;
		ft_mutex_handle(simulation->stop, UNLOCK);
		printf("time: %lu %d %s\n", ft_time() - simulation->start, 
			philo->id, ft_message(opcode));
		ft_mutex_handle(simulation->message, UNLOCK);
		return ;
	}
	else
		printf("%lu %d %s\n", ft_time() - simulation->start,
			philo->id, ft_message(opcode));
	ft_mutex_handle(simulation->message, UNLOCK);
}
