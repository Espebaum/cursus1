/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 14:12:35 by gyopark           #+#    #+#             */
/*   Updated: 2023/02/03 19:45:54 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	child_proc(int *fd, t_token *temp, char **envp, int i)
{
	int		idx;
	char	**arg_cmd;

	idx = 0;
	arg_cmd = (char **)malloc(sizeof(char *) * 10); //일단 10쯤함
	if (i < temp->cmds - 1) //temp->cmds - 1인지 그냥 temp->cmd인지 체크해야함
		dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	while (temp && temp->type != T_PIPE)
	{
		arg_cmd[idx++] = temp->str;
		temp = temp->next;
	}
	arg_cmd[idx] = NULL;
	execute(arg_cmd, envp);
}

void	parent_proc(int *fd)
{
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	close(fd[1]);
}

void	execute(char **arg_cmd, char **envp)
{
	char	*exec_cmd;
	char	**path;

	path = get_path(envp);
	exec_cmd = get_cmd(path, arg_cmd[0]);
	if (!exec_cmd)
		return ;//ft_perror(arg_cmd[0], 127);
	if (execve(exec_cmd, arg_cmd, envp) == -1)
		return ;//ft_perror("execute error", 126);
}

int	open_pipe(t_token *head, char **envp, int cp_stdin)
{
	t_token	*temp;
	int		i;
	int		fd[2];
	pid_t	pid;

	i = -1;
	temp = head->next;
	while (++i < head->cmds)
	{
		if (i)
			temp = get_next_tmp(temp);
		if (pipe(fd) < 0)
			return (exit_error("pipe error", 0, 1));
		set_signal(DFL, DFL);
		pid = fork();
		if (pid == -1)
			return (exit_error("fork error", 0, 1));
		else if (pid == 0)
			child_proc(fd, temp, envp, i);
		set_signal(IGN, IGN);
		parent_proc(fd);
	}
	dup2(cp_stdin, STDIN_FILENO);
	return (wait_all(pid));
}
