/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 16:39:31 by gyopark           #+#    #+#             */
/*   Updated: 2022/11/26 20:41:52 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	ft_print_c(va_list **ap)
{
	unsigned char	vatemp;
	size_t			print_size;

	print_size = 0;
	vatemp = (unsigned char)va_arg(**ap, int);
	print_size = write(1, &vatemp, 1);
	return (print_size);
}

size_t	ft_print_s(va_list **ap)
{
	char	*vatemp;
	size_t	print_size;

	print_size = 0;
	vatemp = (char *)va_arg(**ap, char *);
	if (vatemp == NULL)
		vatemp = "(null)";
	print_size = write(1, vatemp, ft_strlen(vatemp));
	return (print_size);
}
