/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_fork.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 12:39:00 by mohammoh          #+#    #+#             */
/*   Updated: 2024/05/25 12:39:37 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_get_forks(t_philo *philo, t_simulation *sim)
{
	int			first_fork;
	int			second_fork;

	if (philo->id % 2 != 0)
	{
		first_fork = philo->right_fork;
		second_fork = philo->left_fork;
	}
	else
	{
		first_fork = philo->left_fork;
		second_fork = philo->right_fork;
		usleep(10);
	}
	if (ft_check_death_status(sim))
		return ;
	ft_get_forks2(first_fork, second_fork, philo, sim);
}
