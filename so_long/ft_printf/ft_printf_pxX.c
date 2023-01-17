/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_pxX.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 14:01:32 by gyopark           #+#    #+#             */
/*   Updated: 2022/11/30 14:12:09 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_strtoupper(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] >= 'a' && str[i] <= 'z')
			str[i] -= 'a' - 'A';
		i++;
	}
	return (str);
}

ssize_t	ft_print_sx(va_list **ap)
{
	unsigned int		vatemp;
	ssize_t				print_size;
	char				*str;
	int					flag;

	flag = 1;
	print_size = 0;
	vatemp = va_arg(**ap, unsigned int);
	if (vatemp == 0)
		return (write(1, "0", 1));
	str = ft_change_hexa((unsigned int)vatemp, &flag);
	if (flag == 0)
		return (-1);
	print_size = write(1, str, ft_strlen(str));
	free(str);
	return (print_size);
}

ssize_t	ft_print_bx(va_list **ap)
{
	unsigned int		vatemp;
	ssize_t				print_size;
	char				*str;
	int					flag;

	flag = 1;
	print_size = 0;
	vatemp = va_arg(**ap, unsigned int);
	if (vatemp == 0)
		return (write(1, "0", 1));
	str = ft_change_hexa((unsigned)vatemp, &flag);
	if (flag == 0)
		return (-1);
	str = ft_strtoupper(str);
	print_size = write(1, str, ft_strlen(str));
	free(str);
	return (print_size);
}

ssize_t	ft_write_p(ssize_t *print_size, char *str)
{
	*print_size = write(1, "0x", 2);
	if (*print_size == -1)
	{
		free(str);
		return (-1);
	}
	*print_size = write(1, str, ft_strlen(str));
	if (*print_size == -1)
	{
		free(str);
		return (-1);
	}
	free(str);
	return (*print_size);
}

ssize_t	ft_print_p(va_list **ap)
{
	size_t	vatemp;
	ssize_t	print_size;
	char	*str;
	int		flag;

	flag = 1;
	print_size = 0;
	vatemp = (size_t)va_arg(**ap, size_t);
	if (vatemp == 0)
		return (write(1, "0x0", 3));
	str = ft_change_hexa_address((size_t)vatemp, &flag);
	if (flag == 0)
		return (-1);
	print_size = ft_write_p(&print_size, str);
	if (print_size == -1)
		return (-1);
	return (print_size + 2);
}
