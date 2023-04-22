/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoigag <hoigag@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 16:20:45 by hoigag            #+#    #+#             */
/*   Updated: 2023/04/21 18:23:40 by hoigag           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atoi(const char *str)
{
	int		i;
	long	res;

	i = 0;
	res = 0;
	if (str[i] == '-')
		return (0);
	if (str[i] == '+')
		i++;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (0);
		res = res * 10 + (str[i] - '0');
		if (res > INT_MAX)
			return (0);
		i++;
	}
	return (res);
}

int	check_args(char **argv, int argc)
{
	int	i;

	i = 0;
	if (argc != 4 && argc != 5)
	{
		printf("Usage: ./philo number_of_philosophers \
time_to_die time_to_eat time_to_sleep \
[number_of_times_each_philosopher_must_eat]\n");
		return (0);
	}
	while (i < argc)
	{
		if (!ft_atoi(argv[i]))
		{
			printf("Invalid number\n");
			return (0);
		}
		i++;
	}
	return (1);
}

int	init_forks(t_sim *sim)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(&sim->print, NULL) != 0)
	{
		printf("Could not init mutex\n");
		return (0);
	}
	sim->forks = malloc(sizeof(pthread_mutex_t) * sim->number_of_philos);
	if (!sim->forks)
		return (0);
	while (i < sim->number_of_philos)
	{
		if (pthread_mutex_init(&sim->forks[i], NULL) != 0)
		{
			printf("Could not init mutex\n");
			return (0);
		}
		i++;
	}
	return (1);
}

int	init_sim(t_sim *sim, char **argv, int argc)
{
	int	i;

	i = 0;
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
	return (1);
}

t_philo	*create_philosophers(t_sim *sim, int *finish)
{
	t_philo	*philos;
	int		i;
	long	current_time;

	i = 0;
	current_time = get_current_time();
	philos = malloc(sizeof(t_philo) * sim->number_of_philos);
	if (!philos)
		return (0);
	while (i < sim->number_of_philos)
	{
		philos[i].id = i;
		philos[i].is_alive = finish;
		philos[i].is_full = 0;
		philos[i].meal_counter = 0;
		philos[i].current_time = current_time;
		philos[i].last_meal = current_time;
		philos[i].left_fork = &sim->forks[i];
		philos[i].right_fork = &sim->forks[(i + 1) % sim->number_of_philos];
		philos[i].sim = sim;
		i++;
	}
	return (philos);
}
