/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 14:38:31 by mohammoh          #+#    #+#             */
/*   Updated: 2024/05/25 01:38:40 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/**
 * @brief this function will parse the arguments from the command 
 * line and set the data in the simulation struct
 * @param av the arguments from the command line 
 * @param simulation the simulation struct that will hold the data
 * @return 0 if everything is ok
 */
int	ft_parse(char **av, t_simulation *simulation)
{
	int		i;
	int		num;

	i = 0;
	while (av[++i])
	{
		num = ft_atoi(av[i]);
		if (num == -1)
			return (ft_panic("ERROR: INVALID ARGUMENTS\n", 1));
		else if (i == 1)
			set_philosophers(simulation, num);
		else if (i == 2)
			set_time_to_die(simulation, num);
		else if (i == 3)
			set_time_to_eat(simulation, num);
		else if (i == 4)
			set_time_to_sleep(simulation, num);
		else if (i == 5)
			set_max_eat(simulation, num);
	}
	if (av[5] == NULL)
		simulation->max_eat = -4;
	return (0);
}
