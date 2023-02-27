/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_moves.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark < gyopark@student.42seoul.kr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 18:30:39 by gyopark           #+#    #+#             */
/*   Updated: 2023/02/27 13:32:36 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	ft_get_time(void)
{
	struct timeval	tp;

	gettimeofday(&tp, NULL);
	return (tp.tv_sec * 1000 + tp.tv_usec / 1000);
}

void	ft_pass_time(t_arg *arg, long time_to_move)
{
	long	start;
	long	now;

	start = ft_get_time();
	while (check_is_safe(arg) == 1)
	{
		now = ft_get_time();
		if ((now - start) >= time_to_move)
			break ;
	}
}

void	do_think(t_philo *philo, t_arg *arg)
{
	if (check_is_safe(arg) == 0)
	{
		pthread_mutex_lock(&(arg->safe));
		arg->is_safe = 0;
		pthread_mutex_unlock(&(arg->safe));
	}
	else
	{
		ft_philo_print(arg, philo, "is thinking");
	}
}

void	do_sleep(t_philo *philo, t_arg *arg)
{
	if (check_is_safe(arg))
	{
		ft_philo_print(arg, philo, "is sleeping");
		ft_pass_time(arg, arg->time_to_sleep);
	}
}

void	do_eat(t_philo *philo, t_arg *arg)
{
	if (check_is_safe(arg))
	{
		pthread_mutex_lock(&(arg->eats));
		ft_philo_print(arg, philo, "is eating");
		pthread_mutex_unlock(&(arg->eats));
	}
}
