/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 19:20:48 by gyopark           #+#    #+#             */
/*   Updated: 2023/01/10 20:11:45 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	first_child_proc(t_struct cmds, char **argv, char **envp, int *i)
{
	if (is_heredoc(argv[1]))
	{
		dup2(cmds.hfd, STDIN_FILENO);
		close(cmds.hfd);
		*i = 3;
	}
	else
	{
		dup2(cmds.ifd, STDIN_FILENO);
		close(cmds.ifd);
		*i = 2;
	}
	dup2(cmds.fd[1], STDOUT_FILENO);
	close(cmds.fd[0]);
	execute(cmds, argv[*i], envp);
}

void	last_child_proc(t_struct cmds, char **argv, char **envp)
{
	int		ofd;

	if (is_heredoc(argv[1]))
		ofd = open(argv[cmds.argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		ofd = open(argv[cmds.argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (ofd == -1)
		ft_perror("outfile error", EXIT_FAILURE);
	dup2(ofd, STDOUT_FILENO);
	close(ofd);
	execute(cmds, argv[cmds.argc - 2], envp);
}

void	child_proc(t_struct cmds, char *arg, char **envp)
{
	dup2(cmds.fd[1], STDOUT_FILENO);
	close(cmds.fd[0]);
	execute(cmds, arg, envp);
}

void	parent_proc(t_struct cmds)
{
	dup2(cmds.fd[0], STDIN_FILENO);
	close(cmds.fd[0]);
	close(cmds.fd[1]);
}

int	parse_cmd(t_struct cmds, char **argv, char **envp)
{
	pid_t	pid;
	int		i;

	i = 1;
	while (++i < cmds.argc - 1)
	{
		if (pipe(cmds.fd) == -1)
			ft_perror("pipe : ", EXIT_FAILURE);
		pid = fork();
		if (pid == -1)
			ft_perror("fork : ", EXIT_FAILURE);
		else if (pid == 0)
		{
			if (i == 2)
				first_child_proc(cmds, argv, envp, &i);
			if (i == cmds.argc - 2)
				last_child_proc(cmds, argv, envp);
			child_proc(cmds, argv[i], envp);
		}
		parent_proc(cmds);
	}
	return (waitpid(pid, NULL, WNOHANG));
}
