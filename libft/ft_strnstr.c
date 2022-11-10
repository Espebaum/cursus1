/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 17:31:37 by gyopark           #+#    #+#             */
/*   Updated: 2022/11/09 19:27:04 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;

	if (!(*little))
		return ((char *)big);
	while (*big != '\0' && len--)
	{
		i = 0;
		while (*(big + i) == *(little + i) && i < len)
		{
			i++;
			if (*(little + i) == '\0')
				return ((char *)big);
		}
		big++;
	}
	return (0);
}
