/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 13:59:40 by gyopark           #+#    #+#             */
/*   Updated: 2023/01/31 16:37:58 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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

int	here_doc(t_struct cmds, char *limiter)
{
	char	*line;

	cmds.hfd = open("/tmp/.here_doc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (cmds.hfd == -1)
		ft_perror("here_doc", EXIT_FAILURE);
	while (1)
	{
		write(1, "heredoc> ", 9);
		line = get_next_line(STDIN_FILENO);
		if (!line || ft_strncmp(line, limiter, ft_strlen(line)) == 0)
		{
			free(line);
			break ;
		}
		write(cmds.hfd, line, ft_strlen(line));
		free(line);
	}
	cmds.hfd = open("/tmp/.here_doc", O_RDONLY);
	if (cmds.hfd == -1)
	{
		unlink("/tmp/.here_doc");
		ft_perror("here_doc", EXIT_FAILURE);
	}
	return (cmds.hfd);
}

int	go_heredoc(t_struct cmds, char **argv)
{
	char	*limiter;

	limiter = ft_strjoin(argv[2], "\n");
	if (!limiter)
		ft_perror("no limiter", EXIT_FAILURE);
	cmds.hfd = here_doc(cmds, limiter);
	free(limiter);
	return (cmds.hfd);
}

int	is_heredoc(char *arg)
{
	if (ft_strncmp(arg, "here_doc", ft_strlen(arg)) == 0)
		return (1);
	return (0);
}
