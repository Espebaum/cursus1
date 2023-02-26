/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_starts.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark < gyopark@student.42seoul.kr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 17:18:23 by gyopark           #+#    #+#             */
/*   Updated: 2023/02/26 19:50:54 by gyopark          ###   ########.fr       */
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
	if (arg->is_safe == 1)
	{
		printf("%lldms %d %s \n", now - arg->start_time, phi->id, msg);
	}
	pthread_mutex_unlock(&(arg->print));
	return (0);
}

void	ft_check_die(t_arg *arg)
{
	while (arg->is_safe)
	{
		pthread_mutex_lock(&(arg->eats));
		if (check_eat_time(arg)) //식사 시간 확인
			break ;
		if (arg->max_eat_times != -1) // 인자로 최대 식사횟수를 받았다면
			if (check_eat_num(arg)) // 식사횟수 확인
				break ;
		pthread_mutex_unlock(&(arg->eats));
		usleep(100);
	}
	pthread_mutex_unlock(&(arg->eats));
	finish_thread(arg);
}

int	pickup_fork(t_philo *phi, t_arg *arg)
{
	if (arg->is_safe == 0)
		return (0);
	pthread_mutex_lock(&(arg->check_fork)); //포크 사용여부를 확인할때 스레드 하나만 접근
	if (arg->fork_status[phi->left_fork] == 0
		&& arg->fork_status[phi->right_fork] == 0)
	{
		pthread_mutex_lock(&(arg->forks[phi->left_fork]));
		ft_philo_print(arg, phi, "has taken a fork");
		arg->fork_status[phi->left_fork] = 1;
		pthread_mutex_lock(&(arg->forks[phi->right_fork]));
		ft_philo_print(arg, phi, "has taken a fork");
		arg->fork_status[phi->right_fork] = 1;
		do_eat(phi, arg);
		pthread_mutex_unlock(&(arg->check_fork)); //포크 사용여부 락 해제
		ft_pass_time(arg, arg->time_to_eat); //식사 시간만큼 대기
		arg->fork_status[phi->left_fork] = 0;
		arg->fork_status[phi->right_fork] = 0;
		pthread_mutex_unlock(&(arg->forks[phi->left_fork]));
		pthread_mutex_unlock(&(arg->forks[phi->right_fork]));
		phi->eat_count++;
		return (0);
	}
	pthread_mutex_unlock(&(arg->check_fork));
	return (1);
}

void	*ft_thread(void *philo)
{
	t_philo	*phi;
	t_arg	*arg;

	phi = (t_philo *)philo;
	arg = phi->shared_arg;
	if (phi->id % 2 != 1)
		usleep(1000);
	while (arg->is_safe)
	{
		while (pickup_fork(phi, arg))
			usleep(100);
		do_sleep(phi, arg);
		do_think(phi, arg);
		usleep(100);
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
		if (pthread_create(&(philo[i].thread), NULL, ft_thread, \
							&(philo[i])) == -1)
			return (1);
		i++;
	}
	ft_pass_time(arg, arg->time_to_eat); // 첫 식사가 끝나도록 모니터링 대기?
	ft_check_die(arg); // 철학자가 살아있는지, 정해진 만큼 식사했는지 모니터링?
	return (0);
}
