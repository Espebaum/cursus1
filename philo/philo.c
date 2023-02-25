/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 15:00:15 by gyopark           #+#    #+#             */
/*   Updated: 2023/02/25 16:18:47 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_philo_start(t_arg *arg, t_philo *philo)
{
	int		i;

	i = 0;
	while (i < arg->philo_num)
	{
		philo[i].last_eat_time = ft_get_time();
		if (pthread_create(&(philo[i].thread), NULL, ft_thread, &(philo[i])))
			return (1);
		i++;
	}
	ft_philo_check_finish(arg, philo);
	i = 0;
	while (i < arg->philo_num)
		pthread_join(philo[i++].thread, NULL);
	ft_free_thread(arg, philo);
	return (0);
}

int	ft_philo_init(t_philo **philo, t_arg *arg)
{
	int	i;

	i = 0;
	*philo = malloc(sizeof(t_philo) * arg->philo_num);
	if (!(philo))
		return (1);
	while (i < arg->philo_num)
	{
		(*philo)[i].arg = arg;
		(*philo)[i].id = i;
		(*philo)[i].left = i;
		(*philo)[i].right = (i + 1) % arg->philo_num;
		(*philo)[i].last_eat_time = ft_get_time();
		(*philo)[i].eat_count = 0;
		i++;
	}
	return (0);
}

int	ft_arg_init_mutex(t_arg *arg)
{
	int	i;

	if (pthread_mutex_init(&(arg->print), NULL))
		return (1);
	arg->forks = malloc(sizeof(pthread_mutex_t) * arg->philo_num);
	if (!(arg->forks))
		return (1);
	i = 0;
	while (i < arg->philo_num)
	{
		if (pthread_mutex_init(&(arg->forks[i]), NULL))
			return (1);
		i++;
	}
	return (0);
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
		return (print_err("argument error", 3));
	memset(&arg, 0, sizeof(t_arg));
	errno = ft_arg_init(&arg, argc, argv);
	if (errno)
		return (print_err("arg init error", errno));
	errno = ft_philo_init(&philo, &arg);
	if (errno)
		return (print_err("philo init error", errno));
	errno = ft_philo_start(&arg, philo);
	if (errno)
		return (print_err("philo start error", errno));
	system("leaks philo");
	return (0);
}
