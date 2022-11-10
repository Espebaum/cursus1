/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 15:41:13 by gyopark           #+#    #+#             */
/*   Updated: 2022/11/09 16:17:52 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	src;
	int		end;

	src = c;
	end = ft_strlen((char *)s);
	while (end >= 0)
	{
		if (s[end] == src)
			return (s + end);
		end--;
	}
	return (0);
}
