/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 16:29:12 by gyopark           #+#    #+#             */
/*   Updated: 2023/01/10 21:12:24 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	command_not_found(char *cmd)
{
	int	exit_code;

	exit_code = 127;
	ft_perror(cmd, exit_code);
}

int	ft_perror(char *str, int exit_code)
{
	perror(str);
	exit(exit_code);
}

void	cmd_error_handle(char *cmd)
{
	int	exit_code;

	if (!ft_strchr(cmd, '/'))
		command_not_found(cmd);
	open(cmd, O_RDWR);
	if (errno == ENOENT)
		exit_code = 64;
	else if (errno == EACCES)
		exit_code = 13;
	else if (errno == EISDIR)
		exit_code = 21;
	else
		exit_code = EXIT_FAILURE;
	ft_perror(cmd, exit_code);
}

void	error_handle(char *message, char **argv)
{
	int	exit_code;

	if (access(argv[1], X_OK) == -1)
		exit_code = 13;
	else
		exit_code = EXIT_FAILURE;
	ft_perror(message, exit_code);
}
