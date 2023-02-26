/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark < gyopark@student.42seoul.kr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 17:28:25 by gyopark           #+#    #+#             */
/*   Updated: 2023/02/26 19:44:58 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	finish_thread(t_arg *arg)
{
	int		i;

	i = 0;
	while (i < arg->philo_num)
	{
		pthread_join(arg->philo[i].thread, NULL);
		i++;
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
}

int	check_is_num(char *str)
{
	int		i;

	i = -1;
	while (str[++i])
		if (!ft_isdigit(str[i]))
			return (1);
	return (0);
}

long	ft_get_time(void)
{
	struct timeval	tp;

	gettimeofday(&tp, NULL);
	return (tp.tv_sec * 1000 + tp.tv_usec / 1000);
}

void	ft_pass_time(t_arg *arg, long time_to_move)
{
	long long	start;
	long long	now;

	start = ft_get_time();
	while (arg->is_safe == 1)
	{
		now = ft_get_time();
		if ((now - start) >= time_to_move)
			break ;
	}
}
