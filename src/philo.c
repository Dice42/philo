/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 14:14:05 by mohammoh          #+#    #+#             */
/*   Updated: 2024/05/24 23:16:53 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int ac, char **av)
{
	t_simulation simulation;
	t_philo *philo = NULL;

	if (ac == 5 || ac == 6)
	{
		//1- parsing
		if(ft_parse(av, &simulation))
			return (ft_putstr_fd("error parsing the values\n", 2), 0);
		philo = ft_philo_init(&simulation);
		ft_start_simulation(philo, &simulation);
		}
	else 
		ft_putstr_fd("Error: wrong number of arguments\n", 2);
	ft_free(&simulation, philo);
}

