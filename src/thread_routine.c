/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 16:59:37 by mohammoh          #+#    #+#             */
/*   Updated: 2024/05/23 17:07:02 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philo.h"

int		has_both_forks(t_philo *philo)
{
	t_fork	*forks;
	t_simulation	*sim;

	sim = philo->simulation;
	forks = sim->forks;
	if (philo->id % 2 == 0)
	{
		if (forks[philo->right_fork].last_picked != philo->id
			&& forks[philo->left_fork].last_picked != philo->id)
			return (YES);
	}
	else
	{
		if (forks[philo->right_fork].last_picked != philo->id
			&& forks[philo->left_fork].last_picked != philo->id)
			return (YES);
	}
	return (NO);
}