/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_line2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 14:19:35 by youngski          #+#    #+#             */
/*   Updated: 2023/02/07 16:54:22 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
			{
				signo = WTERMSIG(status);
				if (signo == SIGINT && i++ == 0)
					printf("\n");
				if (signo == SIGQUIT && i++ == 0)
					printf("Quit: 3\n");
				g_exit_code = 128 + signo;
			}
			else
				g_exit_code = WEXITSTATUS(status);
		}
	}
	return (g_exit_code);
}

char	**keep_execve(t_data data, t_token **head, char **t, int *flag)
{
	char	**ret;
	char	*cmd;

	cmd = (*head)->str;
	if (cmd[0] == '\0' || (!(check_command(data.path, cmd) \
		&& !builtin_check(cmd)) && *flag == 0))
		exit_error(cmd, 0, 127);
	if ((*head)->cmds == 1 && (!(check_command(data.path, cmd) \
		&& !builtin_check(cmd))) && *flag == 0)
		exit_error(cmd, 0, 127);
	ret = copy_orders(t);
	ret = add_order(ret, cmd, *flag);
	(*head) = (*head)->next;
	*flag = 1;
	return (ret);
}

char	**read_cmd(t_data *data, t_token **head, int flag, int *heredoc_count)
{
	char	**t;

	t = (char **)malloc(sizeof(char *));
	t[0] = 0;
	init_fd(data);
	while ((*head) && (*head)->str && ft_strncmp((*head)->str, "|", 1))
	{
		if (ft_strncmp((*head)->str, ">>", 2) == 0
			&& (*head)->type == T_REDIRECT)
			data->io_fd[1] = append_redirection(data->io_fd[1], head, data);
		else if (ft_strncmp((*head)->str, "<<", 2) == 0
			&& (*head)->type == T_REDIRECT)
			data->io_fd[0] = heredoc_redirection(data->io_fd[0], head, data, \
			heredoc_count);
		else if (ft_strncmp((*head)->str, "<", 1) == 0
			&& (*head)->type == T_REDIRECT)
			data->io_fd[0] = input_redirection(data->io_fd[0], head, data);
		else if (ft_strncmp((*head)->str, ">", 1) == 0
			&& (*head)->type == T_REDIRECT)
			data->io_fd[1] = output_redirection(data->io_fd[1], head, data);
		else
			t = keep_execve(*data, head, t, &flag);
	}
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
    if (access(argv[0], X_OK) == 0)
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

void	init_fd(t_data *data)
{
	data->i_flag = 0;
	data->o_flag = 0;
	data->io_fd[0] = dup(0);
	data->io_fd[1] = dup(1);
}

void	forked_child_work(t_data *data, t_token **head, int *pipes,
		int *heredoc_count)
{
	char	**t;
	char	*cmd;

	t = read_cmd(data, head, 0, heredoc_count);
	dup_pipes(head, pipes, data);
	if ((*head) && (*head)->next)
		(*head) = (*head)->next;
	cmd = find_path(t, data->envp, 0);
	if (check_builtin(t) == -1)
		exit(126);
	if (execve(cmd, t, data->envp) == -1)
		exit(126);
}