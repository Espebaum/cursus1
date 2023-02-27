/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_checks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark < gyopark@student.42seoul.kr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 17:28:25 by gyopark           #+#    #+#             */
/*   Updated: 2023/02/27 13:36:33 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_eat_time(t_arg *arg)
{
	long		time;
	int			i;

	i = 0;
	while (i < arg->philo_num)
	{
		pthread_mutex_lock(&(arg->time));
		time = ft_get_time() - arg->philo[i].last_eat_time;
		pthread_mutex_unlock(&(arg->time));
		if (time > (long)arg->time_to_die)
		{
			pthread_mutex_lock(&(arg->print));
			pthread_mutex_lock(&(arg->safe));
			arg->is_safe = 0;
			pthread_mutex_unlock(&(arg->safe));
			printf("%ldms %d is died\n", \
					ft_get_time() - arg->start_time, arg->philo[i].id);
			pthread_mutex_unlock(&(arg->print));
			return (1);
		}
		i++;
	}
	return (0);
}

int	is_philo_all_eat(t_arg *arg)
{
	long	time;

	pthread_mutex_lock(&(arg->print));
	pthread_mutex_lock(&(arg->safe));
	arg->is_safe = 0;
	pthread_mutex_unlock(&(arg->safe));
	time = ft_get_time();
	printf("%ldms all philo eat %d time\n", \
			time - arg->start_time, arg->max_eat_times);
	pthread_mutex_unlock(&(arg->print));
	return (1);
}

int	check_eat_num(t_arg *arg)
{
	int			i;
	int			check;
	int			eat_count;

	i = 0;
	check = 0;
	while (i < arg->philo_num)
	{
		pthread_mutex_lock(&(arg->e_count));
		eat_count = arg->philo[i].eat_count;
		pthread_mutex_unlock(&(arg->e_count));
		if (eat_count >= arg->max_eat_times && arg->max_eat_times != -1)
			check++;
		i++;
	}
	if (check == arg->philo_num)
		return (is_philo_all_eat(arg));
	return (0);
}

int	check_is_safe(t_arg *arg)
{
	pthread_mutex_lock(&(arg->safe));
	if (arg->is_safe == 0)
	{
		pthread_mutex_unlock(&(arg->safe));
		return (0);
	}	
	pthread_mutex_unlock(&(arg->safe));
	return (1);
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
