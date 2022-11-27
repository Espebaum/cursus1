/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ltoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 13:48:58 by gyopark           #+#    #+#             */
/*   Updated: 2022/11/27 13:57:59 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_len(long long *num)
{
	int				len;
	long long		tmp;

	len = 0;
	if (*num <= 0)
	{
		len += 1;
		*num *= -1;
	}
	tmp = *num;
	while (tmp)
	{
		len += 1;
		tmp /= 10;
	}
	return (len);
}

char	*ft_ltoa(long long num)
{
	size_t		len;
	char		*ascii;

	len = ft_len(&num);
	ascii = (char *) malloc(sizeof(char) * (len + 1));
	if (ascii == NULL)
		return (NULL);
	ascii[len] = '\0';
	ascii[0] = '-';
	while (1)
	{
		ascii[--len] = num % 10 + '0';
		num /= 10;
		if (num == 0)
			break ;
	}
	return (ascii);
}
