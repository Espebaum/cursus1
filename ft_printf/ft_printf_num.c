/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_num.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 17:36:40 by gyopark           #+#    #+#             */
/*   Updated: 2022/11/26 20:41:41 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	ft_print_d(va_list **ap)
{
	int		vatemp;
	char	*str;
	size_t	print_size;

	print_size = 0;
	vatemp = (int)va_arg(**ap, int);
	if (vatemp == 0)
		print_size = write(1, "0", 1);
	else
	{
		str = ft_itoa(vatemp);
		print_size = write(1, str, ft_strlen(str));
		free(str);
	}
	return (print_size);
}

size_t	ft_print_i(va_list **ap)
{
	int		vatemp;
	char	*str;
	size_t	print_size;

	print_size = 0;
	vatemp = (int)va_arg(**ap, int);
	if (vatemp == 0)
		print_size = write(1, "0", 1);
	else
	{
		str = ft_itoa(vatemp);
		print_size = write(1, str, ft_strlen(str));
		free(str);
	}
	return (print_size);
}

size_t
