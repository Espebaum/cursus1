/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark < gyopark@student.42seoul.kr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 15:21:58 by gyopark           #+#    #+#             */
/*   Updated: 2023/02/11 18:21:21 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	src;
	int		len;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	src = c;
	while (len-- >= 0)
	{
		if (*s == src)
			return ((char *)s);
		s++;
	}
	return (NULL);
}
