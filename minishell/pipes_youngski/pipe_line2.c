/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_line2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark < gyopark@student.42seoul.kr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 14:19:35 by youngski          #+#    #+#             */
/*   Updated: 2023/02/12 19:27:13 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	change_stream(t_token **head, t_data *data, int *cmd_flag, \
						int *heredoc_count)
{
	if (ft_strncmp((*head)->str, ">>", 2) == 0 \
		&& (*head)->type == T_REDIRECT)
		data->io_fd[1] = append_redirection(data->io_fd[1], \
							head, data, cmd_flag[1]);
	else if (ft_strncmp((*head)->str, "<<", 2) == 0
		&& (*head)->type == T_REDIRECT)
		data->io_fd[0] = heredoc_redirection(head, \
							data, heredoc_count, cmd_flag[1]);
	else if (ft_strncmp((*head)->str, "<", 1) == 0
		&& (*head)->type == T_REDIRECT)
		data->io_fd[0] = input_redirection(data->io_fd[0], \
							head, data, cmd_flag[1]);
	else if (ft_strncmp((*head)->str, ">", 1) == 0
		&& (*head)->type == T_REDIRECT)
		data->io_fd[1] = output_redirection(data->io_fd[1], \
							head, data, cmd_flag[1]);
}

char	**push_cmd(t_data *data, t_token **head, int *cmd_flag, int *hdoc_count)
{
	char	**t;

	t = (char **)malloc(sizeof(char *));
	t[0] = 0;
	while ((*head) && (*head)->str && ft_strncmp((*head)->str, "|", 1))
	{
		if ((*head)->type == T_REDIRECT && (!ft_strncmp((*head)->str, ">>", 2)
				|| !ft_strncmp((*head)->str, "<<", 2)
				|| !ft_strncmp((*head)->str, "<", 1)
				|| !ft_strncmp((*head)->str, ">", 1)))
			change_stream(head, data, cmd_flag, hdoc_count);
		else
		{
			if (cmd_flag[1] == 1)
				t = keep_execve_par(head, t, cmd_flag);
			else if (cmd_flag[1] == 0)
				t = keep_execve_chd(*data, head, t, cmd_flag);
		}
	}
	return (t);
}

char	**read_cmd(t_data *data, t_token **head, int *heredoc_count)
{
	char	**t;
	int		*cmd_flag;

	cmd_flag = (int *)malloc(sizeof(int) * 2);
	cmd_flag[0] = 0;
	cmd_flag[1] = 0;
	if ((*head)->str == NULL)
	{
		cmd_flag[1] = 1;
		(*head) = (*head)->next;
	}
	init_fd(data);
	t = push_cmd(data, head, cmd_flag, heredoc_count);
	free(cmd_flag);
	return (t);
}

char	*find_path(char *argv[], char **envp, int i)
{
	int		k;
	char	**path;
	char	*sp_path;
	char	**temp;

	if (access(argv[0], X_OK) != -1)
		return (argv[0]);
	k = -1;
	while (envp[++k])
	{
		if (!ft_strncmp("PATH", envp[k], 4))
			break ;
	}
	path = ft_split(envp[k] + 5, ':');
	argv[i] = ft_strjoin("/", argv[i]);
	k = -1;
	while (path[++k])
	{
		temp = ft_split(argv[i], ' ');
		sp_path = ft_strjoin(path[k], temp[0]);
		if (access(sp_path, X_OK) == 0)
			return (sp_path);
	}
	return (0);
}

void	forked_child_work(t_data *data, t_token **head, int *pipes,
		int *heredoc_count, t_list *env_head)
{
	char	**t;
	char	*cmd;
	int		ret;

	t = read_cmd(data, head, heredoc_count);
	dup_pipes(head, pipes, data);
	if ((*head) && (*head)->next)
		(*head) = (*head)->next;
	cmd = find_path(t, data->envp, 0);
	ret = check_builtin(t, env_head);
	if (ret >= 0)
		exit(ret);
	if (execve(cmd, t, data->envp) == -1)
		exit(126);
}
