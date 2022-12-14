/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 15:41:13 by gyopark           #+#    #+#             */
/*   Updated: 2022/11/24 16:45:09 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	src;
	int		end;

	src = c;
	end = ft_strlen(s);
	while (end >= 0)
	{
		if (s[end] == src)
			return ((char *)(s + end));
		end--;
	}
	return (0);
}
