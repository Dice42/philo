/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 14:38:31 by mohammoh          #+#    #+#             */
/*   Updated: 2024/05/19 14:39:04 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"



/**
 * @brief Sets the number of philosophers in the simulation struct.
 * @param simulation The simulation struct that will hold the data.
 * @param num The number of philosophers.
 * @return 0 if successful, otherwise an error code.
 */
static int set_philosophers(t_simulation *simulation, int num)
{
	if (num == 0)
		return ft_panic("ERROR: NO PHILOSOPHER IN THE TABLE\n", 1);
	simulation->philo_numbers = num;
	return 0;
}

/**
 * @brief Sets the time to die in the simulation struct.
 * @param simulation The simulation struct that will hold the data.
 * @param num The time to die in milliseconds.
 * @return 0 if successful, otherwise an error code.
 */
static int set_time_to_die(t_simulation *simulation, int num)
{
	if (num < 60)
		return ft_panic("ERROR: Time to die cant be less than 60 ms\n", 1);
	simulation->time_to_die = num * 1000;
	return 0;
}

/**
 * @brief Sets the time to eat in the simulation struct.
 * @param simulation The simulation struct that will hold the data.
 * @param num The time to eat in milliseconds.
 * @return 0 if successful, otherwise an error code.
 */
static int set_time_to_eat(t_simulation *simulation, int num)
{
	if (num < 60)
		return ft_panic("ERROR: Time to eat cant be less than 60 ms\n", 1);
	simulation->time_to_eat = num * 1000;
	return 0;
}

/**
 * @brief Sets the time to sleep in the simulation struct.
 * @param simulation The simulation struct that will hold the data.
 * @param num The time to sleep in milliseconds.
 * @return 0 if successful, otherwise an error code.
 */
static int set_time_to_sleep(t_simulation *simulation, int num)
{
	if (num < 60)
		return ft_panic("ERROR: Time to sleep cant be less than 60 ms\n", 1);
	simulation->time_to_sleep = num * 1000;
	return 0;
}

/**
 * @brief Sets the maximum number of meals in the simulation struct.
 * @param simulation The simulation struct that will hold the data.
 * @param num The maximum number of meals.
 * @return 0 if successful, otherwise an error code.
 */
static int set_max_eat(t_simulation *simulation, int num)
{
	if (num < 1)
		return ft_panic("ERROR: Number of meals cant be less than 1\n", 1);
	else if (num >= 1)
		simulation->max_eat = num;
	else
		simulation->max_eat = -1;
	return 0;
}

/**
 * @brief this function will parse the arguments from the command line and set the data in the simulation struct
 * @param av the arguments from the command line 
 * @param simulation the simulation struct that will hold the data
 * @return 0 if everything is ok
 */
int			ft_parse(char **av, t_simulation *simulation)
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
	return (0);
}

