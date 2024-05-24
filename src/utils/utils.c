/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 15:25:22 by mohammoh          #+#    #+#             */
/*   Updated: 2024/05/24 23:09:35 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

char		*ft_message(int opcode)
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

void		ft_print_message(t_philo *philo, t_simulation *simulation, int opcode) // still need to add mutex for stop in to not get a mutex
{
	
	ft_mutex_handle(simulation->message, LOCK);
	if (opcode == DIED)
	{
		ft_mutex_handle(simulation->stop, LOCK);
		simulation->stop_simulation = 1;
		ft_mutex_handle(simulation->stop, UNLOCK);
		printf("time: %lu %d %s\n", ft_time() - simulation->start, philo->id, ft_message(opcode));
		ft_mutex_handle(simulation->message, UNLOCK);
		return ; 
	}
	if (opcode == DONE)
	{
		ft_mutex_handle(simulation->stop, LOCK);
		simulation->stop_simulation = 2;
		printf("%lu %d %s\n", ft_time() - simulation->start, philo->id, ft_message(opcode));
		ft_mutex_handle(simulation->stop, UNLOCK);
		ft_mutex_handle(simulation->message, UNLOCK);
		return ;
	}
	printf("%lu %d %s\n", ft_time() - simulation->start, philo->id, ft_message(opcode));
	ft_mutex_handle(simulation->message, UNLOCK);
}


int			ft_panic(char *message, int ret)
{
	return (ft_putstr_fd(message, 2), exit(1), ret);
}

int ft_strlen(char *s)
{
	int i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	write (fd, s, ft_strlen(s));
}