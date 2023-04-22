/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoigag <hoigag@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 17:10:12 by hoigag            #+#    #+#             */
/*   Updated: 2023/04/21 18:25:46 by hoigag           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

	start = get_current_time();
	while (get_current_time() < time + start)
	{
		if (!*philo->is_alive)
			break ;
		usleep(80);
	}
}

void	print(char *message, t_philo *philo)
{
	if (*philo->is_alive)
	{
		pthread_mutex_lock(&philo->sim->print);
		printf("%ld %d %s\n",
			get_current_time() - philo->current_time,
			philo->id + 1, message);
		pthread_mutex_unlock(&philo->sim->print);
	}
}
