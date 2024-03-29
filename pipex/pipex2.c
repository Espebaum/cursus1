/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 19:20:48 by gyopark           #+#    #+#             */
/*   Updated: 2023/01/14 14:12:41 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execute(t_struct cmds, char *arg, char **envp)
{
	char	**arg_cmd;
	char	*exec_cmd;

	arg_cmd = check_commands(arg);
	exec_cmd = get_cmd(cmds.path, arg_cmd[0]);
	if (!exec_cmd)
		ft_perror(arg_cmd[0], 127);
	if (execve(exec_cmd, arg_cmd, envp) == -1)
		ft_perror("execute error", 126);
}

void	first_child_proc(t_struct cmds, char **argv, char **envp)
{
	close(cmds.fd[0]);
	cmds.ifd = open_file(cmds, argv, argv[1], INFILE);
	if (cmds.ifd == -1)
		ft_perror(argv[1], EXIT_FAILURE);
	dup2(cmds.ifd, STDIN_FILENO);
	dup2(cmds.fd[1], STDOUT_FILENO);
	close(cmds.ifd);
	close(cmds.fd[1]);
	execute(cmds, argv[2], envp);
}

void	second_child_proc(t_struct cmds, char **argv, char **envp)
{
	int		ofd;

	ofd = open_file(cmds, argv, argv[cmds.argc - 1], OUTFILE);
	if (ofd == -1)
		ft_perror(argv[cmds.argc - 1], EXIT_FAILURE);
	dup2(ofd, STDOUT_FILENO);
	close(ofd);
	close(cmds.fd[0]);
	close(cmds.fd[1]);
	execute(cmds, argv[cmds.argc - 2], envp);
}

void	parent_proc(t_struct cmds)
{
	dup2(cmds.fd[0], STDIN_FILENO);
	close(cmds.fd[0]);
	close(cmds.fd[1]);
}

int	open_pipe(t_struct cmds, char **argv, char **envp)
{
	pid_t	pid;
	int		i;

	i = 1;
	while (++i < 4)
	{
		if (pipe(cmds.fd) == -1)
			ft_perror("pipe error", EXIT_FAILURE);
		pid = fork();
		if (pid == -1)
			ft_perror("fork error", EXIT_FAILURE);
		else if (pid == 0)
		{
			if (i == 2)
				first_child_proc(cmds, argv, envp);
			if (i == 3)
				second_child_proc(cmds, argv, envp);
		}
		parent_proc(cmds);
	}
	return (wait_all(pid));
}
