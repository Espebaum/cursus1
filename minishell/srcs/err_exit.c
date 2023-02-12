/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark < gyopark@student.42seoul.kr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 16:25:28 by gyopark           #+#    #+#             */
/*   Updated: 2023/02/12 19:22:18 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exit_error(char *message, int signal, int exit_code)
{
	char	*error_str;

	error_str = strerror(errno);
	write(2, message, ft_strlen(message));
	write(2, ": ", 2);
	write(2, "command not found\n", ft_strlen("command not found\n"));
	g_exit_code = exit_code + signal;
	exit (g_exit_code);
	return (1);
}
//23 write(2, error_str, ft_strlen(error_str));

int	ft_perror(char *str, int signal, int exit_code)
{
	perror(str);
	g_exit_code = exit_code + signal;
	exit(g_exit_code);
}
