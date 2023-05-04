/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoigag <hoigag@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 16:21:24 by hoigag            #+#    #+#             */
/*   Updated: 2023/05/04 14:38:37 by hoigag           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void static	eat(t_philo *philo)
{
	print("is eating", philo);
	pthread_mutex_lock(&philo->sim->print);
	philo->last_meal = get_current_time();
	pthread_mutex_unlock(&philo->sim->print);
	philo->meal_counter++;
	if (philo->meal_counter == philo->sim->number_of_times_to_eat)
	{
		pthread_mutex_lock(&philo->sim->print);
		philo->is_full = 1;
		pthread_mutex_unlock(&philo->sim->print);
	}
	philo_sleep(philo, philo->sim->time_to_eat);
}

void	*routine(void *data)
{
	t_philo			*philo;
	int				stop;

	philo = (t_philo *) data;
	if (philo->id % 2 != 0)
		usleep(10000);
	stop = 1;
	while (stop)
	{
		print("is thinking", philo);
		pthread_mutex_lock(philo->left_fork);
		print("has taken a fork", philo);
		pthread_mutex_lock(philo->right_fork);
		print("has taken a fork", philo);
		eat(philo);
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		print("is sleeping", philo);
		philo_sleep(philo, philo->sim->time_to_sleep);
		pthread_mutex_lock(&philo->sim->print);
		stop = ((*philo->is_alive) && (!philo->is_full));
		pthread_mutex_unlock(&philo->sim->print);
	}
	return (0);
}

int	check_full(t_sim *sim)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (i < sim->number_of_philos)
	{
		pthread_mutex_lock(&sim->print);
		if (sim->philosophers[i].is_full)
			counter++;
		pthread_mutex_unlock(&sim->print);
		i++;
	}
	return (counter == sim->number_of_philos);
}

int	check_death(t_philo *philo, int *finish)
{
	long	period;

	pthread_mutex_lock(&philo->sim->print);
	period = get_current_time() - philo->last_meal;
	pthread_mutex_unlock(&philo->sim->print);
	if (period > philo->sim->time_to_die)
	{
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

int	join_and_free(t_sim *sim)
{
	int	i;

	i = 0;
	while (i < sim->number_of_philos)
	{
		if (pthread_join(sim->philo_threads[i], 0) != 0)
		{
			printf("could not join thread\n");
			return (0);
		}
		i++;
	}
	if (!destroy_mutexes(sim))
		return (0);
	free(sim->forks);
	free(sim->philosophers);
	free(sim->philo_threads);
	return (1);
}
