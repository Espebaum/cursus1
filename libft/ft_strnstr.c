/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 17:31:37 by gyopark           #+#    #+#             */
/*   Updated: 2022/11/12 17:47:40 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;

	if (!(*needle) || len == 0 || haystack == needle)
		return ((char *)haystack);
	while (*haystack != '\0' && len--)
	{
		i = 0;
		while (*(haystack + i) == *(needle + i) && i < len)
		{
			i++;
			if (*(needle + i) == '\0')
				return ((char *)haystack);
		}
		haystack++;
	}
	return (NULL);
}
