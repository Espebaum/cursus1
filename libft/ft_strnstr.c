/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 17:31:37 by gyopark           #+#    #+#             */
/*   Updated: 2022/11/18 18:11:32 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	h_len;
	size_t	n_len;

	if (*needle == '\0')
		return ((char *)haystack);
	h_len = ft_strlen(haystack);
	n_len = ft_strlen(needle);
	if (h_len < n_len || len < n_len)
		return (NULL);
	while (len-- >= n_len && *haystack)
	{
		if (ft_memcmp(haystack, needle, n_len) == 0)
			return ((char *)haystack);
		haystack++;
	}
	return (NULL);
}
