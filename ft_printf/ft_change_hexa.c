/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_change_hexa.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 14:05:54 by gyopark           #+#    #+#             */
/*   Updated: 2022/11/28 20:28:29 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

const char	*g_base1 = "0123456789abcdef";

size_t	ft_hexalen(size_t num)
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

char	*ft_change_hexa(unsigned int vatemp)
{
	size_t		size;
	char		*hexa;
	long long	num;

	size = ft_hexalen(vatemp);
	hexa = (char *)malloc(sizeof(char) * (size + 1));
	hexa[size] = '\0';
	num = vatemp;
	while (num || size)
	{
		hexa[size - 1] = g_base1[num % 16];
		num /= 16;
		size--;
	}
	return (hexa);
}
