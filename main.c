/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoigag <hoigag@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 16:09:42 by hoigag            #+#    #+#             */
/*   Updated: 2023/04/25 11:46:38 by hoigag           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *data)
{
	t_philo			*philo;

	philo = (t_philo *) data;
	if (philo->id % 2 != 0)
		usleep(10000);
	while (*philo->is_alive && !philo->is_full)
	{
		print("is thinking", philo);
		pthread_mutex_lock(philo->left_fork);
		print("has taken a fork", philo);
		pthread_mutex_lock(philo->right_fork);
		print("has taken a fork", philo);
		print("is eating", philo);
		philo->last_meal = get_current_time();
		philo->meal_counter++;
		if (philo->meal_counter == philo->sim->number_of_times_to_eat)
			philo->is_full = 1;
		philo_sleep(philo, philo->sim->time_to_eat);
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		print("is sleeping", philo);
		philo_sleep(philo, philo->sim->time_to_sleep);
	}
	return (0);
}

int	check_full(t_philo *philosophers, t_sim sim)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (i < sim.number_of_philos)
	{
		if (philosophers[i].is_full)
			counter++;
		i++;
	}
	return (counter == sim.number_of_philos);
}

int	check_death(t_philo *philo, int *finish)
{
	if (get_current_time() - philo->last_meal > philo->sim->time_to_die)
	{
		pthread_mutex_lock(&philo->sim->eat);
		*finish = 0;
		pthread_mutex_lock(&philo->sim->print);
		printf("%ld %d %s\n",
			get_current_time() - philo->current_time,
			philo->id + 1, "died");
		pthread_mutex_unlock(&philo->sim->print);
		if (philo->sim->number_of_philos == 1)
			pthread_mutex_unlock(philo->left_fork);
		return (1);
	}
	return (0);
}

int	monitor(t_philo *philosophers, t_sim sim, int *finish)
{
	int	i;

	i = 0;
	if (sim.number_of_times_to_eat > 0)
	{
		if (check_full(philosophers, sim))
			return (1);
	}
	if (check_death(&philosophers[i], finish))
		return (1);
	i++;
	i = i % sim.number_of_philos;
	return (0);
}

int	main(int argc, char **argv)
{
	t_sim		sim;
	t_philo		*philosophers;
	pthread_t	*philo_threads;
	int			i;
	int			finish;

	finish = 1;
	i = 0;
	if (!check_args(argv + 1, argc - 1))
		return (ERROR);
	if (!init_sim(&sim, argv + 1, argc - 1))
		return (ERROR);
	philosophers = create_philosophers(&sim, &finish);
	if (!philosophers)
	{
		printf("could not create philosophers\n");
		return (ERROR);
	}
	philo_threads = malloc(sizeof(pthread_t) * sim.number_of_philos);
	if (!philo_threads)
		return (ERROR);
	while (i < sim.number_of_philos)
	{
		if (pthread_create(&philo_threads[i], NULL,
				routine, &philosophers[i]) != 0)
		{
			printf("could not create thread\n");
			return (ERROR);
		}
		usleep(10);
		i++;
	}
	while (1)
	{
		if (monitor(philosophers, sim, &finish))
			break ;
	}
	i = 0;
	while (i < sim.number_of_philos)
	{
		if (pthread_join(philo_threads[i], NULL) != 0)
		{
			printf("could not join thread\n");
			return (ERROR);
		}
		i++;
	}
	return (0);
}
