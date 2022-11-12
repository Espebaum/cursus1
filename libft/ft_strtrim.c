/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 15:34:40 by gyopark           #+#    #+#             */
/*   Updated: 2022/11/12 20:22:07 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*strtrim;
	char	*start;
	char	*end;

	if (!s1)
		return (0);
	start = (char *)s1;
	end = (char *)s1 + ft_strlen(s1);
	while (*start)
	{
		if (!ft_strchr(set, *start))
			break ;
		start++;
	}
	while (start != NULL && start < end)
	{
		if (!ft_strchr(set, *end))
			break;
		end--;
	}
	strtrim = (char *)malloc(end - start + 2);
	if (!strtrim)
		return (NULL);
	ft_strlcpy(strtrim, start, end - start + 2);
	return (strtrim);
}
