/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 16:28:04 by gyopark           #+#    #+#             */
/*   Updated: 2022/11/30 13:13:50 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

ssize_t	print_va(const char *str, va_list *ap)
{
	ssize_t	print_size;

	print_size = 0;
	if (str[1] == 'c')
		print_size = ft_print_c(&ap);
	else if (str[1] == 's')
		print_size = ft_print_s(&ap);
	else if (str[1] == 'd')
		print_size = ft_print_d(&ap);
	else if (str[1] == 'i')
		print_size = ft_print_i(&ap);
	else if (str[1] == 'u')
		print_size = ft_print_u(&ap);
	else if (str[1] == '%')
		print_size = write(1, "%%", 1);
	else if (str[1] == 'x')
		print_size = ft_print_sx(&ap);
	else if (str[1] == 'X')
		print_size = ft_print_bx(&ap);
	else if (str[1] == 'p')
		print_size = ft_print_p(&ap);
	return (print_size);
}

int	ft_printf(const char *str, ...)
{
	va_list	ap;
	int		i;
	ssize_t	print_size;
	ssize_t	past_print_size;

	i = 0;
	print_size = 0;
	va_start(ap, str);
	while (str[i])
	{
		past_print_size = print_size;
		if (str[i] != '%')
			print_size += write(1, &str[i], 1);
		else
			print_size += print_va(&str[i++], &ap);
		if (past_print_size > print_size)
		{
			print_size = -1;
			va_end(ap);
			return (print_size);
		}
		i++;
	}
	va_end(ap);
	return ((int)print_size);
}
