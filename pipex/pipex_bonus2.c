/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 19:20:48 by gyopark           #+#    #+#             */
/*   Updated: 2023/01/08 14:35:00 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	child_proc(t_struct cmds, int i, char **argv, char **envp)
{
	if (i == 0)
		first_child_proc(cmds, argv, envp);
	else if (i == cmds.pipe_size - 1)
		last_child_proc(cmds, i, argv, envp);
	else
		mid_parent_proc(cmds, i, argv, envp);
}

void	parent_proc(t_struct cmds, int i, char **argv, char **envp)
{
	if (i == 0)
		first_parent_proc(cmds, argv, envp);
	else if (i == cmds.pipe_size - 1)
		last_parent_proc(cmds, i, argv, envp);
	else
		mid_parent_proc(cmds, i, argv, envp);
}

int	odd_even_pipe_bonus(t_struct cmds, char **argv, char **envp, int i)
{
	int		result;
	pid_t	pid;

	result = 0;
	i = -1;
	while (++i < cmds.pipe_size)
	{
		if (!(i % 2))
			if (pipe(cmds.pipeA) < 0)
				exit(1);
		if (i % 2)
			if (pipe(cmds.pipeB) < 0)
				exit(1);
		pid = fork();
		if (pid == -1)
			exit (1);
		else if (!pid)
			child_proc(cmds, i, argv, envp);
		else
			parent_proc(cmds, i, argv, envp);
	}
	return (result);
}

int	parse_cmd(t_struct cmds, char **argv, char **envp)
{
	int		i;
	char	**arg_cmd1;
	char	**arg_cmd2;
	int		result;

	result = 0;
	i = -1;
	while (++i < cmds.pipe_size)
	{
		arg_cmd1 = check_commands(argv[i + 2]);
		arg_cmd2 = check_commands(argv[i + 3]);
		cmds.cmd1 = get_cmd(cmds.path, arg_cmd1[0]);
		cmds.cmd2 = get_cmd(cmds.path, arg_cmd2[1]);
		if (!cmds.cmd1 || !cmds.cmd2)
			perror("command not found");
		result = odd_even_pipe_bonus(cmds, argv, envp, i);
	}
	return (result);
}
