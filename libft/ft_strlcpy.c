/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 15:03:49 by gyopark           #+#    #+#             */
/*   Updated: 2022/11/08 15:19:36 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	ft_strlcpy(char *dest, char *src, unsigned int size)
{
	char	*c;
	int		cnt;

	c = src;
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
