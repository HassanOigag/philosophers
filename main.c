/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoigag <hoigag@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 16:09:42 by hoigag            #+#    #+#             */
/*   Updated: 2023/05/06 20:18:10 by hoigag           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	monitor(t_sim *sim, int *finish)
{
	int	i;

	i = 0;
	while (i < sim->number_of_philos)
	{
		if (check_death(&sim->philosophers[i], finish))
			return (1);
		if (sim->number_of_times_to_eat > 0)
		{
			if (check_full(sim))
			{
				pthread_mutex_lock(&sim->print);
				*finish = 0;
				pthread_mutex_unlock(&sim->print);
				return (1);
			}
		}
		i++;
	}
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
	{
		free(sim.forks);
		free(sim.philosophers);
		free(sim.philo_threads);
		return (ERROR);
	}
	return (0);
}
