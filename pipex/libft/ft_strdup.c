/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 13:14:21 by gyopark           #+#    #+#             */
/*   Updated: 2022/12/02 19:11:05 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	s1_len;
	char	*mem;

	s1_len = ft_strlen(s1);
	mem = (char *)malloc(sizeof(char) * s1_len + 1);
	if (mem != NULL)
	{
		ft_memcpy(mem, s1, s1_len);
		mem[s1_len] = '\0';
	}
	return (mem);
}
