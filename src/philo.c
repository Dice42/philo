/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 14:14:05 by mohammoh          #+#    #+#             */
/*   Updated: 2024/05/19 19:14:48 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int ac, char **av)
{
	int i = -1;
	t_simulation simulation;
	t_philo *philo;
	
	i = -1;
	if (ac == 5 || ac == 6)
	{
		//1- parsing
		if(ft_parse(av, &simulation))
			return (ft_putstr_fd("error parsing the values\n", 2), 0);
		//2- data initalizing
		philo = ft_philo_init(&simulation);

		// print all the philo stucture compenent
		while (++i < simulation.philo_numbers)
		{
			printf("philo id: %d\n", philo[i].id);
			printf("philo left fork: %d\n", philo[i].left_fork);
			printf("philo right fork: %d\n", philo[i].right_fork);
			printf("philo eating time: %d\n", philo[i].eating_time);
			printf("philo is dead: %d\n", philo[i].is_dead);
			printf("philo max eat: %d\n", philo[i].max_eat);
			printf("----------------------------------------\n" );
		}

		//print all the simulation stucture compenent
		printf("num of philo  [%d]\n", simulation.philo_numbers);
		printf("time_to_die   [%dms]\n", simulation.time_to_die);
		printf("time_to_eat   [%dms]\n", simulation.time_to_eat);
		printf("time_to_sleep [%dms]\n", simulation.time_to_sleep);
		printf("max_eat       [%d]\n", simulation.max_eat);
		printf("----------------------------------------\n" );
		
		
		// // // 3- start simulation dining
		ft_start_simulation(philo, &simulation);
		printf("%d\n", simulation.philo_numbers);
		printf("time_to_die   %dms\n", simulation.time_to_die);
		printf("time_to_eat   %dms\n", simulation.time_to_eat);
		printf("time_to_sleep %dms\n", simulation.time_to_sleep);
	}
	else 
		ft_putstr_fd("Error: wrong number of arguments\n", 2);
}
