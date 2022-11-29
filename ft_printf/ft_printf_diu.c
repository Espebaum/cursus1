/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_diu.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 17:36:40 by gyopark           #+#    #+#             */
/*   Updated: 2022/11/29 20:48:12 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

ssize_t	ft_print_d(va_list **ap)
{
	int		vatemp;
	char	*str;
	ssize_t	print_size;

	print_size = 0;
	vatemp = (int)va_arg(**ap, int);
	if (vatemp == 0)
		print_size = write(1, "0", 1);
	else
	{
		str = ft_itoa(vatemp);
		if (!str)
			return (-1);
		print_size = write(1, str, ft_strlen(str));
		free(str);
	}
	return (print_size);
}

ssize_t	ft_print_i(va_list **ap)
{
	int		vatemp;
	char	*str;
	ssize_t	print_size;

	print_size = 0;
	vatemp = (int)va_arg(**ap, int);
	if (vatemp == 0)
		print_size = write(1, "0", 1);
	else
	{
		str = ft_itoa(vatemp);
		if (!str)
			return (-1);
		print_size = write(1, str, ft_strlen(str));
		free(str);
	}
	return (print_size);
}

ssize_t	ft_print_u(va_list **a)
{
	unsigned int	vatemp;
	char			*str;
	ssize_t			print_size;

	print_size = 0;
	vatemp = (unsigned int)va_arg(**a, unsigned int);
	if (vatemp == 0)
		print_size = write(1, "0", 1);
	else
	{
		str = ft_ltoa(vatemp);
		if (!str)
			return (-1);
		print_size = write(1, str, ft_strlen(str));
		free(str);
	}
	return (print_size);
}
