/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 16:52:56 by gyopark           #+#    #+#             */
/*   Updated: 2022/11/26 20:41:43 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include "./libft/libft.h"
# include <stdio.h>

int		ft_printf(const char *str, ...);
size_t	print_va(const char *str, va_list *ap);
size_t	ft_print_c(va_list **ap);
size_t	ft_print_s(va_list **ap);
size_t	ft_print_d(va_list **ap);
size_t	ft_print_i(va_list **ap);
size_t	ft_print_u(va_list **ap);
size_t	ft_print_x(va_list **ap);
size_t	ft_print_X(va_list **ap);
size_t	ft_print_p(va_list **ap);

#endif
