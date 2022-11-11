/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 14:56:46 by gyopark           #+#    #+#             */
/*   Updated: 2022/11/11 17:26:56 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	len;
	char			*new_s;
	unsigned int	index;

	new_s = NULL;
	index = 0;
	len = ft_strlen(s);
	if (!(new_s == (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	while (index++ < len)
		new_s[index] = f(index, s[index]);
	new_s[index] = '\0';
	return (new_s);
}
