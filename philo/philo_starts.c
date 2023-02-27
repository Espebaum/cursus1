/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_starts.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark < gyopark@student.42seoul.kr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 17:18:23 by gyopark           #+#    #+#             */
/*   Updated: 2023/02/27 13:47:23 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_philo_print(t_arg *arg, t_philo *phi, char *msg)
{
	long long	now;

	now = ft_get_time();
	if (now == -1)
	{
		return (-1);
	}
	pthread_mutex_lock(&(arg->print));
	if (check_is_safe(arg) == 1)
	{
		printf("%lldms %d %s \n", now - arg->start_time, phi->id, msg);
	}
	pthread_mutex_unlock(&(arg->print));
	return (0);
}

int	pickup_fork2(t_philo *phi, t_arg *arg)
{
	pthread_mutex_lock(&(arg->forks[phi->left_fork]));
	ft_philo_print(arg, phi, "has taken a fork");
	arg->fork_status[phi->left_fork] = 1;
	pthread_mutex_lock(&(arg->forks[phi->right_fork]));
	ft_philo_print(arg, phi, "has taken a fork");
	arg->fork_status[phi->right_fork] = 1;
	do_eat(phi, arg);
	pthread_mutex_unlock(&(arg->check_fork));
	ft_pass_time(arg, arg->time_to_eat);
	pthread_mutex_lock(&(arg->time));
	phi->last_eat_time = ft_get_time();
	pthread_mutex_unlock(&(arg->time));
	pthread_mutex_lock(&(arg->check_fork));
	arg->fork_status[phi->right_fork] = 0;
	arg->fork_status[phi->left_fork] = 0;
	pthread_mutex_unlock(&(arg->check_fork));
	pthread_mutex_unlock(&(arg->forks[phi->right_fork]));
	pthread_mutex_unlock(&(arg->forks[phi->left_fork]));
	pthread_mutex_lock(&(arg->e_count));
	phi->eat_count++;
	pthread_mutex_unlock(&(arg->e_count));
	return (0);
}

int	pickup_fork1(t_philo *phi, t_arg *arg)
{
	if (check_is_safe(arg) == 0)
		return (0);
	pthread_mutex_lock(&(arg->check_fork));
	if (arg->fork_status[phi->left_fork] == 0
		&& arg->fork_status[phi->right_fork] == 0)
		return (pickup_fork2(phi, arg));
	pthread_mutex_unlock(&(arg->check_fork));
	return (1);
}

void	*ft_thread(void *philo)
{
	t_philo	*phi;
	t_arg	*arg;

	phi = (t_philo *)philo;
	arg = phi->shared_arg;
	if (!phi->id % 2)
		usleep(1000);
	while (check_is_safe(arg))
	{
		while (pickup_fork1(phi, arg))
			;
		do_sleep(phi, arg);
		do_think(phi, arg);
	}
	return (0);
}

int	ft_start_philo(t_arg *arg, t_philo *philo)
{
	int		i;

	i = 0;
	arg->start_time = ft_get_time();
	while (i < arg->philo_num)
	{
		philo[i].last_eat_time = ft_get_time();
		if (pthread_create(&(philo[i].thread), NULL, ft_thread, \
							&(philo[i])))
			return (1);
		i++;
	}
	ft_pass_time(arg, arg->time_to_eat);
	ft_check_die(arg);
	return (0);
}
