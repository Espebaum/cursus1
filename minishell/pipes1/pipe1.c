/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 14:12:35 by gyopark           #+#    #+#             */
/*   Updated: 2023/02/02 17:30:44 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

child_proc(t_token *head, int i)
{
	char	*cmd
}

int	open_pipe(t_token *head, int cp_stdin)
{
	int	i;
	int	fd[2];
	pid_t	pid;

	i = -1;
	while (++i < head->cmds)
	{
		if (pipe(fd) < 0)
			return (exit_error("pipe error", NULL, 1));
		pid = fork();
		if (pid == -1)
			return (exit_error("fork error", NULL, 1));
		if (pid == 0)
			child_proc(head, i);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
	}
	dup2(cp_stdin, STDIN_FILENO);
	return (wait_all(pid));
}