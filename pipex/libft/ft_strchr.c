/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 15:21:58 by gyopark           #+#    #+#             */
/*   Updated: 2022/11/24 16:14:03 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	src;
	int		len;

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
