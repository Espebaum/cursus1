/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 19:20:48 by gyopark           #+#    #+#             */
/*   Updated: 2023/01/06 20:47:26 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pipe_inter(int pid, t_struct cmds)
{
	if (pid == 0)
	{
		close(cmds.fd[0]);
		dup2(cmds.infile, STDIN_FILENO);
		dup2(cmds.fd[1], STDOUT_FILENO);
		close(cmds.infile);
		close(cmds.fd[1]);
	}
	else if (pid > 0)
	{
		close(cmds.fd[1]);
		dup2(cmds.fd[0], STDIN_FILENO);
		dup2(cmds.outfile, STDOUT_FILENO);
		close(cmds.outfile);
		close(cmds.fd[0]);
	}
}

void	open_pipe(t_struct cmds, char **arg_cmd1, char **arg_cmd2, char **envp)
{
	pid_t	pid;

	pipe(cmds.fd);
	pid = fork();
	if (pid == 0)
	{
		pipe_inter(pid, cmds);
		if (execve(cmds.cmd1, arg_cmd1, envp) == -1)
			exit_err("execute error!");
	}
	else if (pid > 0)
	{
		pipe_inter(pid, cmds);
		waitpid(pid, NULL, WNOHANG);
		if (execve(cmds.cmd2, arg_cmd2, envp) == -1)
			exit_err("execute error!");
	}
	else
		exit_err("fork fail");
}

int	parse_cmd(t_struct cmds, char **argv, char **envp)
{
	char	**arg_cmd1;
	char	**arg_cmd2;
	int		result;

	result = 0;
	arg_cmd1 = check_commands(argv[2]);
	arg_cmd2 = check_commands(argv[3]);
	cmds.cmd1 = get_cmd(cmds.path, arg_cmd1[0]);
	cmds.cmd2 = get_cmd(cmds.path, arg_cmd2[0]);
	if (!cmds.cmd1 || !cmds.cmd2)
		perror("command not found");
	open_pipe(cmds, arg_cmd1, arg_cmd2, envp);
	return (result);
}
