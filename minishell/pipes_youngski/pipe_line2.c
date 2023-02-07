/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_line2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 14:19:35 by youngski          #+#    #+#             */
/*   Updated: 2023/02/07 22:34:04 by gyopark          ###   ########.fr       */
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
	char	**ret;
	char	*cmd;

	cmd = (*head)->str;
	if (cmd != NULL) //명령어가 NULL이 아니면 판단
	{
		if (cmd_flag[0] == 0) //첫번째 명령어일 때 -> 확인해야함 //첫번째 명령어 아니면 그냥 박음
		{
			if (builtin_check(cmd) == 0) //일치하는 builtin이 있다면 1, 없다면 0을 리턴, 빌트인이 없다면 명령어 검사
				if (check_command(data.path, cmd) == 0) //일치하는 command가 있다면 1, 없다면 0을 리턴, 명령어가 없다면 부모/자식에 따라 반환/종료
					exit_error(cmd, 0, 127);
			if (cmd[0] == '/')
			{
				if (access(cmd, X_OK) == -1)
				{
					ft_putstr_fd(cmd, 2);
					write(2, ": ", 2);
					ft_putstr_fd("is a directory\n", 2);
					exit (126);
				}

			}
		}
	}
	else //명령어가 NULL이면 종료
		exit_error(cmd, 0, 127);
	ret = copy_orders(t);
	ret = add_order(ret, cmd, cmd_flag[0]);
	(*head) = (*head)->next;
	cmd_flag[0] = 1;
	return (ret);
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
		{
			if (cmd_flag[1] == 1)
				t = keep_execve_par(head, t, cmd_flag);
			else if (cmd_flag[1] == 0)
				t = keep_execve_chd(*data, head, t, cmd_flag);
		}
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