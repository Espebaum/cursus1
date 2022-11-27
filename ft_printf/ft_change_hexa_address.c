/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_change_hexa_address.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 15:39:50 by gyopark           #+#    #+#             */
/*   Updated: 2022/11/27 17:20:08 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

const char	*g_base2 = "0123456789abcdef";

char	*ft_change_hexa_address(long long vatemp)
{
	char				*addr;
	unsigned long long	p;
	size_t				len;

	p = (unsigned long long)&vatemp;
	addr = (char *)malloc(sizeof(char) * 13);
	addr[12] = '\0';
	len = 11;
	while (len)
	{
		addr[len] = g_base2[p % 16];
		p /= 16;
		len--;
	}
	return (addr);
}
