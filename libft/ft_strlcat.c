/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 13:09:16 by gyopark           #+#    #+#             */
/*   Updated: 2022/11/10 11:33:29 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>

unsigned int	ft_strlcat(char *dest, const char *src, size_t size)
{
	unsigned int	p_dest;
	unsigned int	p_src;
	unsigned int	dest_len;
	unsigned int	src_len;

	dest_len = ft_strlen(dest);
	src_len = ft_strlen(src);
	p_dest = dest_len;
	p_src = 0;
	while (src[p_src] && (p_src + dest_len + 1) < size)
		dest[p_dest++] = src[p_src++];
	dest[p_dest] = '\0';
	if (dest_len < size)
		return (src_len + dest_len);
	else
		return (src_len + size);
}
