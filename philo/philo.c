/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark < gyopark@student.42seoul.kr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 16:02:31 by gyopark           #+#    #+#             */
/*   Updated: 2023/02/26 17:01:24 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_is_num(char *str)
{
	int		i;

	i = -1;
	while (str[++i])
		if (!ft_isdigit(str[i]))
			return (1);
	return (0);
}

int	check_argv(int argc, char **argv, t_arg **arg)
{
	int		i;

	i = 0;
	while (++i != argc)
		if (check_is_num(argv[i]))
			return (1);
	if (ft_atoi(argv[1]) < 1 || ft_atoi(argv[2]) < 0 || ft_atoi(argv[3]) < 0
		|| ft_atoi(argv[4]) < 0)
		return (1);
	if (argc == 6)
		if (ft_atoi(argv[5]) < 0)
			return (1);
	(*arg)->philo_num = ft_atoi(argv[1]);
	(*arg)->time_to_die = ft_atoi(argv[2]);
	(*arg)->time_to_eat = ft_atoi(argv[3]);
	(*arg)->time_to_sleep = ft_atoi(argv[4]);
	return (0);
}

int	ft_arg_init(int argc, char **argv, t_arg *arg)
{
	int	i;

	i = -1;
	if (check_argv(argc, argv, &arg))
		return (3);
	arg->max_eat_times = -1;
	if (argc == 6)
	{
		arg->max_eat_times = ft_atoi(argv[5]);
		if (arg->max_eat_times == 0)
			return (3);
	}
	arg->fork_status = (int *)malloc(sizeof(int) * arg->philo_num);
	if (arg->fork_status == NULL)
		return (3);
	while (i < arg->philo_num)
		arg->fork_status[++i] = 0;
	arg->is_safe = 1;
	//if (ft_philo_init(arg) || ft_mutex_init(arg))
	//	return (3);
	return (0);
}

int	main(int argc, char **argv)
{
	t_arg	arg;
	int		errno;

	if (argc != 5 && argc != 6)
		return (print_err("argument error", 3));
	memset(&arg, 0, sizeof(t_arg));
	errno = ft_arg_init(argc, argv, &arg);
	if (errno)
		return (print_err("arg init error", errno));
	printf("errno : %d\n", errno);
	return (0);
}
