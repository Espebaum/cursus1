/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 19:13:16 by gyopark           #+#    #+#             */
/*   Updated: 2023/02/23 19:31:32 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <string.h>

typedef struct s_arg
{
	int		philo_num;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		start_time;
	int		eat_times;
}	t_arg;

typedef struct s_philo
{
	int		b;
}	t_philo;

int		ft_atoi(const char *str);

#endif
