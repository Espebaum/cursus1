/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_change_hexa_address.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 15:39:50 by gyopark           #+#    #+#             */
/*   Updated: 2022/11/28 20:13:41 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

const char	*g_base2 = "0123456789abcdef";

char	*ft_change_hexa_address(size_t vatemp)
{
	char	*addr;
	size_t	addr_len;
	size_t	p;

	p = vatemp;
	addr_len = ft_hexalen(vatemp);
	addr = (char *)malloc(sizeof(char) * (addr_len + 1));
	addr[addr_len] = '\0';
	while (p || addr_len)
	{
		addr[addr_len - 1] = g_base2[p % 16];
		p /= 16;
		addr_len--;
	}
	return (addr);
}
