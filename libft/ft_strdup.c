/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 13:14:21 by gyopark           #+#    #+#             */
/*   Updated: 2022/11/10 16:53:50 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcpy(char *dest, char *src)
{
	char	*p;

	p = dest;
	while (*src)
		*p++ = *src++;
	*p = '\0';
	return (dest);
}

char	*ft_strdup(char *src)
{
	int		src_len;
	char	*mem;

	src_len = ft_strlen(src);
	mem = (char *)malloc(sizeof(char) * src_len + 1);
	if (mem != NULL)
		ft_strcpy(mem, src);
	return (mem);
}
