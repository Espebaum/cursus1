/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_line2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 14:19:35 by youngski          #+#    #+#             */
/*   Updated: 2023/02/09 17:24:34 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	with_signal_exit(int *signo, int *status, int *i)
{
	*signo = WTERMSIG(*status);
	if (*signo == SIGINT && (*i)++ == 0)
		printf("\n");
	if (*signo == SIGQUIT && (*i)++ == 0)
		printf("Quit: 3\n");
	g_exit_code = 128 + *signo;
	return (g_exit_code);
}

int	wait_all(pid_t last_pid)
{
	pid_t	pid;
	int		signo;
	int		status;
	int		i;

	i = 0;
	pid = 1;
	while (pid != -1)
	{
		pid = wait(&status);
		if (pid == last_pid)
		{
			if (WIFSIGNALED(status))
				g_exit_code = with_signal_exit(&signo, &status, &i);
			else
				g_exit_code = WEXITSTATUS(status);
		}
	}
	return (g_exit_code);
}

char	**keep_execve_par(t_token **head, char **builtin, int *cmd_flag)
{
	char	**ret;
	char	*cmd;

	cmd = (*head)->str;
	ret = copy_orders(builtin);
	ret = add_order(ret, cmd, cmd_flag[0]);
	(*head) = (*head)->next;
	cmd_flag[0] = 1;
	return (ret);
}

char	**keep_execve_chd(t_data data, t_token **head, char **t, int *cmd_flag)
{
	char		**ret;
	char		*cmd;
	struct stat	file_info;

	cmd = (*head)->str;
	lstat(cmd, &file_info);
	if (cmd != NULL && cmd[0] != '\0')
	{
		if (cmd_flag[0] == '\0')
			if (builtin_check(cmd) == 0)
				if (check_command(data.path, cmd) == 0
					|| S_ISDIR(file_info.st_mode))
					exit_error(cmd, 0, 127);
	}
	else
		exit_error(cmd, 0, 127);
	ret = copy_orders(t);
	ret = add_order(ret, cmd, cmd_flag[0]);
	(*head) = (*head)->next;
	cmd_flag[0] = 1;
	return (ret);
}

void	change_stream(t_token **head, t_data *data, int *cmd_flag, \
						int *heredoc_count)
{
	if (ft_strncmp((*head)->str, ">>", 2) == 0 \
		&& (*head)->type == T_REDIRECT)
		data->io_fd[1] = append_redirection(data->io_fd[1], \
							head, data, cmd_flag[1]);
	else if (ft_strncmp((*head)->str, "<<", 2) == 0
		&& (*head)->type == T_REDIRECT)
		data->io_fd[0] = heredoc_redirection( \
							head, data, heredoc_count, cmd_flag[1]);
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

	k = -1;
	while (envp[++k])
	{
		if (!ft_strncmp("PATH", envp[k], 4))
			break ;
	}
	path = ft_split(envp[k] + 5, ':');
	if (access(argv[0], X_OK) != -1)
		return (argv[0]);
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
		int *heredoc_count)
{
	char	**t;
	char	*cmd;
	int		ret;

	t = read_cmd(data, head, heredoc_count); //자식, 부모에 따라 진입 시 head 위치가 상이
	dup_pipes(head, pipes, data);
	if ((*head) && (*head)->next)
		(*head) = (*head)->next;
	cmd = find_path(t, data->envp, 0);
	ret = check_builtin(t);
	if (ret >= 0)
		exit(ret);
	if (execve(cmd, t, data->envp) == -1)
		exit(126);
}