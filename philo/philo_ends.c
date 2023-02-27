/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_ends.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark < gyopark@student.42seoul.kr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 13:27:23 by gyopark           #+#    #+#             */
/*   Updated: 2023/02/27 16:26:43 by gyopark          ###   ########.fr       */
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
		usleep(200);
	}
	pthread_mutex_unlock(&(arg->eats));
	finish_thread(arg);
}

void	destroy_mutexs(t_arg *arg)
{
	pthread_mutex_destroy(&(arg->print));
	pthread_mutex_destroy(&(arg->eats));
	pthread_mutex_destroy(&(arg->check_fork));
	pthread_mutex_destroy(&(arg->time));
	pthread_mutex_destroy(&(arg->e_count));
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
	else
		pthread_detach(arg->philo[0].thread);
	i = 0;
	while (i < arg->philo_num)
	{
		pthread_mutex_destroy(&(arg->forks[i]));
		i++;
	}
	free(arg->forks);
	free(arg->philo);
	free(arg->fork_status);
	destroy_mutexs(arg);
}
