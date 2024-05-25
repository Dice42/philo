/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 14:14:05 by mohammoh          #+#    #+#             */
/*   Updated: 2024/05/25 20:10:34 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int ac, char **av)
{
	t_simulation	simulation;
	t_philo			*philo;

	philo = NULL;
	if (ac == 5 || ac == 6)
	{
		if (ft_parse(av, &simulation))
			return (ft_putstr_fd("error parsing the values\n", 2), 0);
		philo = ft_philo_init(&simulation);
		ft_start_simulation(philo, &simulation);
		free(philo);
		ft_free(&simulation);
	}
	else
		ft_putstr_fd("Error: wrong number of arguments\n", 2);
}
