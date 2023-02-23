/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark < gyopark@student.42seoul.kr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 16:02:07 by gyopark           #+#    #+#             */
/*   Updated: 2023/02/23 20:22:21 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_arg_init_mutex(t_arg *arg)
{
	int		i;

	if (pthread_mutex_init(&(arg->print), NULL))
		return (1);
	arg->forks = malloc(sizeof(pthread_mutex_t) * arg->philo_num);
	if (!(arg->forks))
		return (1);
}

int	ft_arg_init(t_arg *arg, int argc, char **argv)
{
	arg->philo_num = ft_atoi(argv[1]);
	arg->time_to_die = ft_atoi(argv[2]);
	arg->time_to_eat = ft_atoi(argv[3]);
	arg->time_to_sleep = ft_atoi(argv[4]);
	arg->start_time = ft_get_time();
	if (arg->philo_num <= 0 || arg->time_to_die < 0 || arg->time_to_eat < 0
		|| arg->time_to_sleep < 0)
	{
		return (5);
	}
	if (argc == 6)
	{
		arg->eat_times = ft_atoi(argv[5]);
		if (arg->eat_times <= 0)
			return (6);
	}
	if (ft_arg_init_mutex(arg))
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_arg		arg;
	t_philo		*philo;
	int			errno;

	if (argc != 5 && argc != 6)
		return (printf("argument error"));
	memset(&arg, 0, sizeof(t_arg));
	errno = ft_arg_init(&arg, argc, argv);
	if (errno)
		return (printf("arg init error"));
	errno = ft_philo_init(&philo, &arg);
	if (errno)
		return (printf("philo init error"));
	errno = ft_philo_start(&arg, philo);
	if (errno)
		return (printf("philo start error"));
	return (0);
}
