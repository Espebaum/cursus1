/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 17:56:50 by gyopark           #+#    #+#             */
/*   Updated: 2022/12/05 21:22:26 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*new_dest;
	unsigned char	*new_src;
	size_t			i;

	if (!dest)
		return (0);
	if (dest == src)
		return (dest);
	new_dest = (unsigned char *) dest;
	new_src = (unsigned char *) src;
	i = 0;
	while (i++ < n)
		*new_dest++ = *new_src++;
	return (dest);
}

size_t	ft_strlen(const char *s)
{
	size_t	cnt;

	cnt = 0;
	if (!s)
		return (0);
	while (*s++)
		cnt++;
	return (cnt);
}

char	*ft_strchr(const char *s, int c)
{
	char	src;
	int		len;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	src = c;
	while (len-- >= 0)
	{
		if (*s == src)
			return ((char *)s);
		s++;
	}
	return (NULL);
}

char	*ft_strdup(char *s1)
{
	size_t	s1_len;
	char	*mem;

	s1_len = ft_strlen(s1);
	mem = (char *)malloc(sizeof(char) * s1_len + 1);
	if (!mem)
		return (NULL);
	ft_memcpy(mem, s1, s1_len);
	mem[s1_len] = '\0';
	return (mem);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*strjoin;
	size_t	len1;
	size_t	len2;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	strjoin = (char *)malloc(sizeof(char) * (len1 + len2 + 1));
	if (!strjoin)
	{
		str_free(&s1);
		return (NULL);
	}
	ft_memcpy(strjoin, s1, len1);
	ft_memcpy(strjoin + len1, s2, len2);
	strjoin[len1 + len2] = '\0';
	str_free(&s1);
	return (strjoin);
}
