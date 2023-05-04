/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoigag <hoigag@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 16:17:12 by hoigag            #+#    #+#             */
/*   Updated: 2023/05/04 15:01:21 by hoigag           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_forks(t_sim *sim)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(&sim->print, 0) != 0
		|| pthread_mutex_init(&sim->last_meal, 0) != 0)
	{
		printf("Could not init mutex\n");
		return (0);
	}
	sim->forks = malloc(sizeof(pthread_mutex_t) * sim->number_of_philos);
	if (!sim->forks)
		return (0);
	while (i < sim->number_of_philos)
	{
		if (pthread_mutex_init(&sim->forks[i], 0) != 0)
		{
			printf("Could not init mutex\n");
			return (0);
		}
		i++;
	}
	return (1);
}

static int	init_philosophers(t_sim *sim, int *finish)
{
	int		i;
	long	current_time;

	i = 0;
	current_time = get_current_time();
	sim->philosophers = malloc(sizeof(t_philo) * sim->number_of_philos);
	if (!sim->philosophers)
		return (0);
	while (i < sim->number_of_philos)
	{
		sim->philosophers[i].id = i;
		sim->philosophers[i].is_alive = finish;
		sim->philosophers[i].is_full = 0;
		sim->philosophers[i].meal_counter = 0;
		sim->philosophers[i].current_time = current_time;
		sim->philosophers[i].last_meal = current_time;
		sim->philosophers[i].left_fork = &sim->forks[i];
		sim->philosophers[i].right_fork = &sim->forks[(i + 1) % sim
			->number_of_philos];
		sim->philosophers[i].sim = sim;
		i++;
	}
	return (1);
}

static int	create_philo_threads(t_sim *sim)
{
	int	i;

	i = 0;
	sim->philo_threads = malloc(sizeof(pthread_t) * sim->number_of_philos);
	if (!sim->philo_threads)
		return (0);
	while (i < sim->number_of_philos)
	{
		if (pthread_create(&sim->philo_threads[i], 0,
				routine, &sim->philosophers[i]) != 0)
		{
			printf("could not create thread\n");
			return (0);
		}
		usleep(10);
		i++;
	}
	return (1);
}

int	init_sim(t_sim *sim, char **argv, int argc, int *finish)
{
	sim->number_of_philos = ft_atoi(argv[0]);
	sim->time_to_die = ft_atoi(argv[1]);
	sim->time_to_eat = ft_atoi(argv[2]);
	sim->time_to_sleep = ft_atoi(argv[3]);
	if (argc == 5)
		sim->number_of_times_to_eat = ft_atoi(argv[4]);
	else
		sim->number_of_times_to_eat = -1;
	if (!init_forks(sim))
		return (0);
	if (!init_philosophers(sim, finish))
	{
		free(sim->forks);
		return (0);
	}
	if (!create_philo_threads(sim))
	{
		free(sim->forks);
		free(sim->philosophers);
		return (0);
	}
	return (1);
}

int	destroy_mutexes(t_sim *sim)
{
	int	i;

	i = 0;
	while (i < sim->number_of_philos)
	{
		if (pthread_mutex_destroy(&sim->forks[i]) != 0)
		{
			printf("could not destroy mutex\n");
			return (0);
		}
		i++;
	}
	if (pthread_mutex_destroy(&sim->print) != 0
		|| pthread_mutex_destroy(&sim->last_meal) != 0)
	{
		printf("could not destroy the print mutex\n");
		return (0);
	}
	return (1);
}
