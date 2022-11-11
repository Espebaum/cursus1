/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 19:54:43 by gyopark           #+#    #+#             */
/*   Updated: 2022/11/11 17:00:39 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_len(int n)
{
	int		len;
	int		tmp;

	len = 0;
	if (n <= 0)
	{
		len += 1;
		n *= -1;
	}
	tmp = n;
	while (tmp)
	{
		len += 1;
		tmp /= 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	int		len;
	char	*ascii;

	len = ft_len(n);
	ascii = (char *) malloc(sizeof(char) * (len + 1));
	if (ascii == NULL)
		return (NULL);
	ascii[len] = 0;
	ascii[0] = '-';
	while (1)
	{
		ascii[--len] = n % 10;
		n /= 10;
		if (n == 0)
			break ;
	}
	return (ascii);
}
