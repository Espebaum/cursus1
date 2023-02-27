/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_ends.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark < gyopark@student.42seoul.kr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 13:27:23 by gyopark           #+#    #+#             */
/*   Updated: 2023/02/27 13:32:34 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_check_die(t_arg *arg)
{
	while (check_is_safe(arg) == 1)
	{
		pthread_mutex_lock(&(arg->eats));
		if (check_eat_time(arg))
			break ;
		if (arg->max_eat_times != -1)
			if (check_eat_num(arg))
				break ;
		pthread_mutex_unlock(&(arg->eats));
	}
	pthread_mutex_unlock(&(arg->eats));
	finish_thread(arg);
}

void	finish_thread(t_arg *arg)
{
	int		i;

	i = 0;
	if (arg->philo_num > 1)
	{
		while (i < arg->philo_num)
		{
			pthread_join(arg->philo[i].thread, NULL);
			i++;
		}
	}
	i = 0;
	while (i < arg->philo_num)
	{
		pthread_mutex_destroy(&(arg->forks[i]));
		i++;
	}
	free(arg->forks);
	free(arg->philo);
	free(arg->fork_status);
	pthread_mutex_destroy(&(arg->print));
	pthread_mutex_destroy(&(arg->eats));
	pthread_mutex_destroy(&(arg->check_fork));
	pthread_mutex_destroy(&(arg->time));
	pthread_mutex_destroy(&(arg->e_count));
}
