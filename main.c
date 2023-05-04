/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoigag <hoigag@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 16:09:42 by hoigag            #+#    #+#             */
/*   Updated: 2023/05/03 15:45:54 by hoigag           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	monitor(t_sim *sim, int *finish)
{
	int	i;

	i = 0;
	if (sim->number_of_times_to_eat > 0)
	{
		if (check_full(sim))
			return (1);
	}
	if (check_death(&sim->philosophers[i], finish))
		return (1);
	i++;
	i = i % sim->number_of_philos;
	return (0);
}

int	main(int argc, char **argv)
{
	t_sim		sim;
	int			i;
	int			finish;

	finish = 1;
	i = 0;
	if (!check_args(argv + 1, argc - 1))
		return (ERROR);
	if (!init_sim(&sim, argv + 1, argc - 1, &finish))
		return (ERROR);
	while (1)
	{
		if (monitor(&sim, &finish))
			break ;
	}
	if (!join_and_free(&sim))
		return (ERROR);
	return (0);
}
