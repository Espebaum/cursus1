/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_change_hexa_address.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 15:39:50 by gyopark           #+#    #+#             */
/*   Updated: 2022/11/30 13:52:42 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_change_hexa_address(size_t vatemp, int *flag)
{
	char		*addr;
	size_t		addr_len;
	const char	*g_base;

	g_base = "0123456789abcdef";
	addr_len = ft_hexalen(vatemp);
	addr = (char *)malloc(sizeof(char) * (addr_len + 1));
	if (!addr)
	{
		free(addr);
		*flag = 0;
		return (NULL);
	}
	addr[addr_len] = '\0';
	while (addr_len)
	{
		addr[addr_len - 1] = g_base[vatemp % 16];
		vatemp /= 16;
		addr_len--;
	}
	return (addr);
}
