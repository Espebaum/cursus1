/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 13:40:07 by gyopark           #+#    #+#             */
/*   Updated: 2022/11/24 16:57:09 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;

	if (len >= ft_strlen(s))
		len = ft_strlen(s);
	if (ft_strlen(s) < start)
		return (ft_strdup(""));
	if (ft_strlen(s) - start < len)
		substr = (char *)malloc(sizeof(char) * (ft_strlen(s) - start) + 1);
	else
		substr = (char *)malloc(sizeof(char) * (len + 1));
	if (!substr)
		return (NULL);
	ft_strlcpy(substr, (char *)(s + start), len + 1);
	return (substr);
}
