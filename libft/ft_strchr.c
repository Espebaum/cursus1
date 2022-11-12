/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 15:21:58 by gyopark           #+#    #+#             */
/*   Updated: 2022/11/11 18:18:01 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	src;
	int		len;

	len = ft_strlen(s);
	src = c;
	while (len >= 0)
	{
		if (*s == src)
			return ((char *)s);
		len--;
		s++;
	}
	return (NULL);
}
