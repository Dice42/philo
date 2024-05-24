     /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_handle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 22:24:57 by mohammoh          #+#    #+#             */
/*   Updated: 2024/04/24 23:24:27 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*ft_save_malloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
		return (ft_panic("ERROR: MALLOC FAILED\n", 0), NULL);
	return (ptr);
}

void	ft_mutex_handle(pthread_mutex_t *mutex, t_opcode opcode)
{
	if (opcode == INIT)
	{
		if (pthread_mutex_init(mutex, NULL))
			ft_panic("ERROR: MUTEX INIT FAILED\n", 0);
	}
	else if (opcode == DESTROY)
	{
		if (pthread_mutex_destroy(mutex))
			ft_panic("ERROR: MUTEX DESTROY FAILED\n", 0);
	}
	else if (opcode == LOCK)
	{
		usleep(50);
		if (pthread_mutex_lock(mutex))
			ft_panic("ERROR: MUTEX LOCK FAILED\n", 0);
	}
	else if (opcode == UNLOCK)
	{
		if (pthread_mutex_unlock(mutex))
			ft_panic("ERROR: MUTEX UNLOCK FAILED\n", 0);
	}
}

void	 ft_thread_handle(pthread_t *thread, t_opcode opcode , void *(*routine)(void *), void *arg)
{
	if (opcode == CREATE)
	{
		if (pthread_create(thread, NULL, routine, arg))
			ft_panic("ERROR: THREAD CREATE FAILED\n", 0);
	}
	else if (opcode == JOIN)
	{
		//might need a pointer in the first arugment (thread)
		if (pthread_join(*thread, NULL))
			ft_panic("ERROR: THREAD JOIN FAILED\n", 0);
	}
	else if (opcode == DETACH)
	{
		//might need a pointer in the first arugment (thread)
		if (pthread_detach(*thread))
			ft_panic("ERROR: THREAD DETACH FAILED\n", 0);
	}
}