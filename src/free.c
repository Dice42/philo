/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 16:59:37 by mohammoh          #+#    #+#             */
/*   Updated: 2024/05/25 01:32:40 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_free(t_simulation *sim)
{
	free(sim->last_meal);
	free(sim->message);
	free(sim->stop);
	free(sim->death);
	free(sim->threads);
	free(sim->forks);
}
