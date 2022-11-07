/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 16:51:14 by gyopark           #+#    #+#             */
/*   Updated: 2022/11/07 17:09:08 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *dest, int c, unsigned int n)
{
	unsigned char	*new_dest;
	unsigned char	src;
	unsigned int	i;

	new_dest = dest;
	src = c;
	i = 0;
	while (i++ < n)
		*new_dest++ = src;
	return (dest);
}
