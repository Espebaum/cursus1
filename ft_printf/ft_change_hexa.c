/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_change_hexa.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 14:05:54 by gyopark           #+#    #+#             */
/*   Updated: 2022/11/27 17:19:33 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

const char	*g_base1 = "0123456789abcdef";

size_t	ft_hexalen(long long num)
{
	int		size;

	size = 0;
	while (num)
	{
		size += 1;
		num /= 16;
	}
	return (size);
}

char	*ft_change_hexa(long long vatemp)
{
	size_t		size;
	size_t		i;
	char		*hexa;
	long long	num;

	size = ft_hexalen(vatemp);
	hexa = (char *)malloc(sizeof(char) * (size + 1));
	hexa[size] = '\0';
	num = vatemp;
	i = 0;
	while (num)
	{
		hexa[i] = g_base1[num / 16];
		i++;
		if (num < 16)
		{
			hexa[i] = g_base1[num % 16];
			break ;
		}
	}
	return (hexa);
}
