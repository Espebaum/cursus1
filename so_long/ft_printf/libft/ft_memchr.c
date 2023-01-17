/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 16:29:54 by gyopark           #+#    #+#             */
/*   Updated: 2022/11/24 15:28:03 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*dest;
	unsigned char	src;

	dest = (unsigned char *)s;
	src = c;
	while (n--)
	{
		if (*dest == src)
			return ((void *)dest);
		dest++;
	}
	return (0);
}
