/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_change_hexa.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 14:05:54 by gyopark           #+#    #+#             */
/*   Updated: 2022/11/30 13:53:12 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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

char	*ft_change_hexa(unsigned int vatemp, int *flag)
{
	size_t		size;
	char		*hexa;
	const char	*g_base;

	g_base = "0123456789abcdef";
	size = ft_hexalen(vatemp);
	hexa = (char *)malloc(sizeof(char) * (size + 1));
	if (!hexa)
	{
		free(hexa);
		*flag = 0;
		return (NULL);
	}
	hexa[size] = '\0';
	while (size)
	{
		hexa[size - 1] = g_base[vatemp % 16];
		vatemp /= 16;
		size--;
	}
	return (hexa);
}
