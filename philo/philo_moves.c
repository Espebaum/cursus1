/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_moves.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark < gyopark@student.42seoul.kr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 18:30:39 by gyopark           #+#    #+#             */
/*   Updated: 2023/02/26 19:41:20 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_eat_time(t_arg *arg)
{
	long long	time;
	int			i;

	i = 0;
	while (i < arg->philo_num)
	{
		time = ft_get_time() - arg->start_time;
		if (time - arg->philo[i].last_eat_time > arg->time_to_die)
		{
			pthread_mutex_lock(&(arg->print));
			arg->is_safe = 0;
			printf("%lldms %d is died\n", time, arg->philo[i].id);
			pthread_mutex_unlock(&(arg->print));
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_eat_num(t_arg *arg)
{
	long long	time;
	int			i;
	int			check;

	i = 0;
	check = 0;
	while (i < arg->philo_num)
	{
		if (arg->philo_num >= arg->max_eat_times && arg->max_eat_times != -1)
			check++;
		i++;
	}
	if (check == arg->philo_num)
	{
		pthread_mutex_lock(&(arg->print));
		arg->is_safe = 0;
		time = ft_get_time() - arg->start_time;
		printf("%lldms all philo eat %d time\n", time, arg->max_eat_times);
		pthread_mutex_unlock(&(arg->print));
		return (1);
	}
	return (0);
}

void	do_think(t_philo *philo, t_arg *arg)
{
	if (arg->is_safe == 0)
		arg->is_safe = 0;
	else
	{
		ft_philo_print(arg, philo, "is thinking");
	}
}

void	do_sleep(t_philo *philo, t_arg *arg)
{
	if (arg->is_safe == 0)
		arg->is_safe = 0;
	else
	{
		ft_philo_print(arg, philo, "is sleeping");
		ft_pass_time(arg, arg->time_to_sleep);
	}
}

void	do_eat(t_philo *philo, t_arg *arg)
{
	long long	time;

	if (arg->is_safe == 0)
		time = 0;
	else
	{
		pthread_mutex_lock(&(arg->eats));
		time = ft_get_time() - arg->start_time;
		philo->last_eat_time = time;
		ft_philo_print(arg, philo, "is eating");
		pthread_mutex_unlock(&(arg->eats));
	}
}
