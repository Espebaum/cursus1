/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark < gyopark@student.42seoul.kr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 16:13:51 by gyopark           #+#    #+#             */
/*   Updated: 2023/02/27 13:32:39 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <unistd.h>

typedef struct s_philo	t_philo;

typedef struct s_arg
{
	int				philo_num;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				max_eat_times;
	long			start_time;
	int				*fork_status;
	int				is_safe;
	t_philo			*philo;
	pthread_mutex_t	print;
	pthread_mutex_t	*forks;
	pthread_mutex_t	check_fork;
	pthread_mutex_t	eats;
	pthread_mutex_t	safe;
	pthread_mutex_t	time;
	pthread_mutex_t	e_count;
}	t_arg;

typedef struct s_philo
{
	int			eat_count;
	long		last_eat_time;
	int			left_fork;
	int			right_fork;
	t_arg		*shared_arg;
	int			id;
	pthread_t	thread;
}	t_philo;

int		ft_atoi(char *str);
int		ft_isdigit(int c);
int		print_err(char *message, int errno);
int		ft_mutex_init(t_arg *arg);
int		check_is_num(char *str);
int		ft_start_philo(t_arg *arg, t_philo *philo);
long	ft_get_time(void);
void	ft_pass_time(t_arg *arg, long time_to_eat);
void	do_eat(t_philo *philo, t_arg *arg);
int		ft_philo_print(t_arg *arg, t_philo *phi, char *msg);
void	do_eat(t_philo *philo, t_arg *arg);
void	do_sleep(t_philo *philo, t_arg *arg);
void	do_think(t_philo *philo, t_arg *arg);
int		check_eat_time(t_arg *arg);
int		check_eat_num(t_arg *arg);
void	finish_thread(t_arg *arg);
int		check_is_safe(t_arg *arg);
void	ft_check_die(t_arg *arg);

#endif