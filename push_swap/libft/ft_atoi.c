/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 19:35:47 by gyopark           #+#    #+#             */
/*   Updated: 2022/11/24 17:27:24 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_space(char c)
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
