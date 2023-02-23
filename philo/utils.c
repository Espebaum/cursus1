/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 19:24:26 by gyopark           #+#    #+#             */
/*   Updated: 2023/02/23 19:25:51 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

int	is_space(char c)
{
	if (c == 9 || c == 10 || c == 11
		|| c == 12 || c == 13 || c == 32)
		return (1);
	else
		return (0);
}

int	ft_atoi(const char *str)
{
	long long	cnt;
	long long	is_minus;

	cnt = 0;
	is_minus = 1;
	while (*str)
	{
		if (is_space(*str))
			str++;
		else
			break ;
	}
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			is_minus *= -1;
		str++;
	}
	while (ft_isdigit(*str))
	{
		cnt *= 10;
		cnt += *str - '0';
		str++;
	}
	return (is_minus * cnt);
}
