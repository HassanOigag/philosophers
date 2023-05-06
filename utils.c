/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoigag <hoigag@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 16:20:45 by hoigag            #+#    #+#             */
/*   Updated: 2023/05/05 13:26:18 by hoigag           ###   ########.fr       */
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

long	get_current_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, 0) == 0)
		return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
	return (0);
}

void	philo_sleep(t_philo	*philo, long time)
{
	long	start;
	int		is_alive;

	start = get_current_time();
	pthread_mutex_lock(&philo->sim->print);
	is_alive = !(*philo->is_alive);
	pthread_mutex_unlock(&philo->sim->print);
	while (get_current_time() < time + start)
	{
		pthread_mutex_lock(&philo->sim->print);
		is_alive = !(*philo->is_alive);
		pthread_mutex_unlock(&philo->sim->print);
		if (is_alive)
			break ;
		usleep(100);
	}
}

void	print(char *message, t_philo *philo)
{
	pthread_mutex_lock(&philo->sim->print);
	if (*philo->is_alive)
	{
		printf("%ld %d %s\n",
			get_current_time() - philo->current_time,
			philo->id + 1, message);
	}
	pthread_mutex_unlock(&philo->sim->print);
}
