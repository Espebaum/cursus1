/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 16:52:56 by gyopark           #+#    #+#             */
/*   Updated: 2023/01/02 14:40:31 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include "./libft/libft.h"

int		ft_printf(const char *str, ...);
ssize_t	print_va(const char *str, va_list *ap);
ssize_t	ft_print_c(va_list **ap);
ssize_t	ft_print_s(va_list **ap);
ssize_t	ft_print_d(va_list **ap);
ssize_t	ft_print_i(va_list **ap);
ssize_t	ft_print_u(va_list **ap);
ssize_t	ft_print_sx(va_list **ap);
ssize_t	ft_print_bx(va_list **ap);
ssize_t	ft_print_p(va_list **ap);

char	*ft_change_hexa(unsigned int vatemp, int *flag);
size_t	ft_hexalen(size_t num);
char	*ft_change_hexa_address(size_t vatemp, int *flag);

#endif
