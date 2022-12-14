/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 13:09:16 by gyopark           #+#    #+#             */
/*   Updated: 2022/11/24 16:32:55 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	p_dst;
	size_t	p_src;
	size_t	dst_len;
	size_t	src_len;

	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	p_dst = dst_len;
	p_src = 0;
	if (dst_len >= dstsize)
		return (src_len + dstsize);
	while (src[p_src] && (p_src + dst_len + 1) < dstsize)
		dst[p_dst++] = src[p_src++];
	dst[p_dst] = '\0';
	return (src_len + dst_len);
}
