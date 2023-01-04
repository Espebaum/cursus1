/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 19:20:48 by gyopark           #+#    #+#             */
/*   Updated: 2023/01/04 22:58:35 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	open_pipe(t_struct cmds, char **arg_cmd1, char **arg_cmd2, char **envp)
{
	pid_t	pid;

	pipe(cmds.fd);
	pid = fork();
	if (pid == 0)
	{
		close(cmds.fd[0]);
		dup2(cmds.infile, STDIN_FILENO);
		dup2(cmds.fd[1], STDOUT_FILENO);
		close(cmds.infile);
		close(cmds.fd[1]);
		execve(cmds.cmd1, arg_cmd1, envp);
	}
	else if (pid > 0)
	{
		close(cmds.fd[1]);
		dup2(cmds.fd[0], STDIN_FILENO);
		dup2(cmds.outfile, STDOUT_FILENO);
		close(cmds.outfile);
		close(cmds.fd[0]);
		waitpid(pid, NULL, WNOHANG);
		execve(cmds.cmd2, arg_cmd2, envp);
	}
	else
		exit_err("fork fail");
}

void	parse_cmd(t_struct cmds, char **argv, char **envp)
{
	char	**arg_cmd1;
	char	**arg_cmd2;

	arg_cmd1 = check_commands(argv[2]);
	arg_cmd2 = check_commands(argv[3]);
	cmds.cmd1 = get_cmd(cmds.path, arg_cmd1[0]);
	cmds.cmd2 = get_cmd(cmds.path, arg_cmd2[0]);
	open_pipe(cmds, arg_cmd1, arg_cmd2, envp);
}
