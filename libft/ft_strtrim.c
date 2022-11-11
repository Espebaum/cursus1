/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 15:34:40 by gyopark           #+#    #+#             */
/*   Updated: 2022/11/10 19:11:20 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_set(char c, char const *set)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*strtrim;
	size_t	start;
	size_t	end;

	if (!s1)
		return (0);
	start = 0;
	end = ft_strlen((char *) s1);
	while (is_set(*(s1 + start), set))
		start++;
	while (is_set(*(s1 + end), set))
		end--;
	if (start > end)
		return (ft_strdup(""));
	strtrim = ft_substr(s1, (unsigned int) s1 + start, end - start);
	return (strtrim);
}
