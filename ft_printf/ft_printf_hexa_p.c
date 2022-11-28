/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_hexa_p.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 14:01:32 by gyopark           #+#    #+#             */
/*   Updated: 2022/11/28 19:36:48 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

ssize_t	ft_print_sx(va_list **a)
{
	unsigned int		vatemp;
	ssize_t				print_size;
	char				*str;

	print_size = 0;
	vatemp = va_arg(**a, int);
	if (vatemp == 0)
		return (write(1, "0", 1));
	str = ft_change_hexa((unsigned int)vatemp);
	print_size = write(1, str, ft_strlen(str));
	free(str);
	return (print_size);
}

ssize_t	ft_print_bx(va_list **a)
{
	unsigned int		vatemp;
	int					i;
	ssize_t				print_size;
	char				*str;

	i = 0;
	print_size = 0;
	vatemp = va_arg(**a, int);
	if (vatemp == 0)
		return (write(1, "0", 1));
	str = ft_change_hexa((unsigned)vatemp);
	while (str[i] != '\0')
	{
		if (str[i] >= 'a' && str[i] <= 'z')
			str[i] -= 'a' - 'A';
		i++;
	}
	print_size = write(1, str, ft_strlen(str));
	free(str);
	return (print_size);
}

ssize_t	ft_print_p(va_list **a)
{
	size_t	vatemp;
	ssize_t	print_size;
	char	*str;

	print_size = 0;
	vatemp = (size_t)va_arg(**a, size_t);
	if (vatemp == 0)
		return (write(1, "0x0", 3));
	str = ft_change_hexa_address((size_t)vatemp);
	print_size = write(1, "0x", 2);
	if (print_size == -1)
		return (print_size);
	print_size = write(1, str, ft_strlen(str));
	if (print_size == -1)
		return (print_size);
	free(str);
	return (print_size + 2);
}
