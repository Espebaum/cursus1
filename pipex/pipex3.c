/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 16:29:12 by gyopark           #+#    #+#             */
/*   Updated: 2023/01/14 13:41:25 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

void	ft_strerror(int errno)
{
	char	*message;

	message = strerror(errno);
	write(2, message, ft_strlen(message));
	write(2, "\n", 1);
	exit(1);
}

int	ft_perror(char *str, int exit_code)
{
	perror(str);
	exit(exit_code);
}
