/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 16:29:12 by gyopark           #+#    #+#             */
/*   Updated: 2023/01/11 21:56:36 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exit_err(const char *str)
{
	perror(str);
	if (ft_strncmp(str, "execute error!", ft_strlen(str)) == 0)
		exit(127);
	else
		exit(1);
}

int	wait_all(pid_t last_pid)
{
	pid_t	pid;
	int		temp;
	int		status;

	pid = 1;
	while (pid != -1)
	{
		pid = wait(&temp);
		if (pid == last_pid)
			status = temp;
	}
	return (status >> 8);
}

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

void	error_handle(char *message, char **argv)
{
	int	exit_code;

	if (access(argv[1], X_OK) == -1)
		exit_code = 13;
	else
		exit_code = EXIT_FAILURE;
	perror(message);
}
