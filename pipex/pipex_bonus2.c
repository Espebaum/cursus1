/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 19:20:48 by gyopark           #+#    #+#             */
/*   Updated: 2023/01/10 14:37:46 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	first_child_proc_bonus(t_struct cmds, char **argv, char **envp)
{
	int		i;

	if (is_heredoc(argv[1]))
	{
		dup2(cmds.hfd, STDIN_FILENO);
		i = 3;
	}
	else
	{
		dup2(cmds.ifd, STDIN_FILENO);
		close(cmds.ifd);
		i = 2;
	}
	dup2(cmds.fd[1], STDOUT_FILENO);
	close(cmds.fd[0]);
	execute_bonus(cmds, argv[i], envp);
}

void	last_child_proc_bonus(t_struct cmds, char **argv, char **envp)
{
	int		ofd;

	if (is_heredoc(argv[1]))
		ofd = open(argv[cmds.argc - 1], O_WRONLY | O_CREAT | O_APPEND, 00644);
	else
		ofd = open(argv[cmds.argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 00644);
	if (ofd == -1)
		perror("outfile error");
	dup2(ofd, STDOUT_FILENO);
	close(ofd);
	execute_bonus(cmds, argv[cmds.argc - 2], envp);
}

void	child_proc_bonus(t_struct cmds, char *arg, char **envp)
{
	dup2(cmds.fd[1], STDOUT_FILENO);
	close(cmds.fd[0]);
	execute_bonus(cmds, arg, envp);
}

void	parent_proc_bonus(t_struct cmds)
{
	dup2(cmds.fd[0], STDIN_FILENO);
	close(cmds.fd[0]);
	close(cmds.fd[1]);
}

int	parse_cmd_bonus(t_struct cmds, char **argv, char **envp)
{
	pid_t	pid;
	int		i;

	i = 1;
	while (++i < cmds.argc - 1)
	{
		if (pipe(cmds.fd) == -1)
			exit_err_bonus("pipe error");
		pid = fork();
		if (pid == -1)
			exit_err_bonus("fork error");
		else if (pid == 0)
		{
			if (i == 2)
				first_child_proc_bonus(cmds, argv, envp);
			if (i == cmds.argc - 2)
				last_child_proc_bonus(cmds, argv, envp);
			child_proc_bonus(cmds, argv[i], envp);
		}
		parent_proc_bonus(cmds);
	}
	return (waitpid(pid, NULL, WNOHANG));
}
