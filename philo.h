/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoigag <hoigag@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 16:00:01 by hoigag            #+#    #+#             */
/*   Updated: 2023/04/20 18:13:55 by hoigag           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <limits.h>

# define ERROR 1

typedef struct s_sim
{
	int				number_of_philos;
	int				number_of_times_to_eat;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	pthread_mutex_t	eat;
}	t_sim;

typedef struct s_philo
{
	int				id;
	int				is_alive;
	int				is_full;
	int				meal_counter;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	long			last_meal;
	long			current_time;
	t_sim			*sim;
}	t_philo;

long	ft_atoi(const char *str);
int		check_args(char **argv, int argc);
int		init_sim(t_sim *sim, char **argv, int argc);
long	get_current_time(void);
t_philo	*create_philosophers(t_sim *sim);
void	philo_sleep(t_philo	*philo, long time);
void	print(char *message, t_philo *philo);
#endif