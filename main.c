/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoigag <hoigag@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 16:09:42 by hoigag            #+#    #+#             */
/*   Updated: 2023/04/20 18:13:28 by hoigag           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *data)
{
	t_philo			*philo;

	philo = (t_philo *) data;
	if (philo->id % 2 == 0)
		usleep(100);
	while (philo->is_alive && !philo->is_full)
	{
		print("is thinking", philo);
		pthread_mutex_lock(philo->left_fork);
		print("has taken a fork", philo);
		pthread_mutex_lock(philo->right_fork);
		print("has taken a fork", philo);
		print("is eating", philo);
		philo->meal_counter++;
		philo->last_meal = get_current_time();
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

int	check_death(t_philo *philosophers, t_sim sim)
{
	int	i;
	int	j;

	i = 0;
	while (i < sim.number_of_philos)
	{
		if (philosophers[i].meal_counter == philosophers[i].sim->number_of_times_to_eat)
			philosophers[i].is_full = 1;
		if (check_full(philosophers, sim))
			return (1);
		if (get_current_time() - philosophers[i].last_meal > philosophers[i].sim->time_to_die)
		{
			print("died", &philosophers[i]);
			if (sim.number_of_philos == 1)
				pthread_mutex_unlock(philosophers[i].left_fork);
			// philosophers[i].is_alive = 0;
			j = 0;
			while (j < sim.number_of_philos)
			{
				philosophers[j].is_alive = 0;
				j++;
			}
			return (1);
		}
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_sim		sim;
	t_philo		*philosophers;
	pthread_t	*philo_threads;
	int			i;

	i = 0;
	if (!check_args(argv + 1, argc - 1))
		return (ERROR);
	if (!init_sim(&sim, argv + 1, argc - 1))
		return (ERROR);
	philosophers = create_philosophers(&sim);
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
		i++;
	}
	while (1)
	{
		if (check_death(philosophers, sim))
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

	// while (i < sim.number_of_philos)
	// {
	// 	printf("----------------------------------\n");
	// 	printf("id : %d\n", philosophers[i].id);
	// 	printf("is alive : %d\n", philosophers[i].is_alive);
	// 	printf("is full : %d\n", philosophers[i].is_full);
	// 	printf("current time : %ld\n", philosophers[i].current_time);
	// 	printf("time to die : %ld\n", philosophers[i].sim->time_to_die);
	// 	printf("time to eat : %ld\n", philosophers[i].sim->time_to_eat);
	// 	printf("time to sleep : %ld\n", philosophers[i].sim->time_to_sleep);
	// 	printf("----------------------------------\n");
	// 	i++;
	// }