/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark < gyopark@student.42seoul.kr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 14:31:38 by gyopark           #+#    #+#             */
/*   Updated: 2023/02/15 21:23:27 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*strjoin;
	size_t	len1;
	size_t	len2;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	strjoin = (char *)malloc(sizeof(char) * (len1 + len2 + 1));
	if (!strjoin)
		return (NULL);
	ft_memcpy(strjoin, s1, len1);
	ft_memcpy(strjoin + len1, s2, len2);
	strjoin[len1 + len2] = '\0';
	return (strjoin);
}

char	*ft_charjoin(char *s1, char s2)
{
	char	*strjoin;
	size_t	len1;
	char	*t;

	t = (char *)malloc(sizeof(char) * 2);
	t[1] = 0;
	t[0] = s2;
	len1 = ft_strlen(s1);
	strjoin = (char *)malloc(sizeof(char) * (len1 + 1 + 1));
	if (!strjoin)
		return (NULL);
	ft_memcpy(strjoin, s1, len1);
	ft_memcpy(strjoin + len1, t, 2);
	strjoin[len1 + 2] = '\0';
	return (strjoin);
}
