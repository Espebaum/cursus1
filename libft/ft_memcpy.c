/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 17:45:33 by gyopark           #+#    #+#             */
/*   Updated: 2022/11/11 20:30:35 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*new_dest;
	unsigned char	*new_src;
	size_t			i;

	if (!n || dest == src)
		return (dest);
	if (dest == NULL && src == NULL)
		return (NULL);
	new_dest = dest;
	new_src = (unsigned char *) src;
	i = 0;
	while (i++ < n)
		*new_dest++ = *new_src++;
	return (dest);
}
