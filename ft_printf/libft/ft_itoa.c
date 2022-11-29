/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 19:54:43 by gyopark           #+#    #+#             */
/*   Updated: 2022/11/29 15:23:58 by gyopark          ###   ########.fr       */
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

char	*ft_itoa(int n)
{
	size_t		len;
	char		*ascii;
	long long	num;

	num = (long long) n;
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
