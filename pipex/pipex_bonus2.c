/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 19:20:48 by gyopark           #+#    #+#             */
/*   Updated: 2023/02/01 15:16:55 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	first_child_proc(t_struct cmds, char **argv, char **envp, int i)
{
	if (is_heredoc(argv[1]))
	{
		cmds.hfd = go_heredoc(cmds, argv);
		dup2(cmds.hfd, STDIN_FILENO);
		close(cmds.hfd);
	}
	else
	{
		cmds.ifd = open_file(cmds, argv, argv[1], INFILE);
		if (cmds.ifd == -1)
			ft_perror(argv[1], EXIT_FAILURE);
		dup2(cmds.ifd, STDIN_FILENO);
		close(cmds.ifd);
	}
	dup2(cmds.fd[1], STDOUT_FILENO);
	close(cmds.fd[0]);
	close(cmds.fd[1]);
	execute(cmds, argv[i], envp);
}

void	last_child_proc(t_struct cmds, char **argv, char **envp)
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

void	child_proc(t_struct cmds, char *arg, char **envp)
{
	dup2(cmds.fd[1], STDOUT_FILENO);
	close(cmds.fd[0]);
	close(cmds.fd[1]);
	execute(cmds, arg, envp);
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

	i = 1 + is_heredoc(argv[1]);
	while (++i < cmds.argc - 1)
	{
		if (pipe(cmds.fd) == -1)
			ft_perror("pipe error", EXIT_FAILURE);
		pid = fork();
		if (pid == -1)
			ft_perror("fork error", EXIT_FAILURE);
		else if (pid == 0)
		{
			if (i == 2 + is_heredoc(argv[1]))
				first_child_proc(cmds, argv, envp, i);
			if (i == cmds.argc - 2)
				last_child_proc(cmds, argv, envp);
			child_proc(cmds, argv[i], envp);
		}
		if (i == 2 && is_heredoc(argv[1]))
			close(cmds.hfd);
		parent_proc(cmds);
	}
	return (wait_all(pid));
}
