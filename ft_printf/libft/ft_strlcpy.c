/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 15:03:49 by gyopark           #+#    #+#             */
/*   Updated: 2022/11/24 17:26:08 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	char	*c;
	size_t	cnt;

	c = (char *)src;
	cnt = 0;
	while (*c)
	{
		c++;
		cnt++;
	}
	if (size)
	{
		while (*src && --size)
		{
			*dest = *src;
			src++;
			dest++;
		}
		*dest = '\0';
	}
	return (cnt);
}
