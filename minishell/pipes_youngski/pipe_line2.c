/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_line2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 14:19:35 by youngski          #+#    #+#             */
/*   Updated: 2023/02/05 20:57:43 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	wait_all(pid_t last_pid)
{
	pid_t	pid;
	int		temp;
	int		signo;
	int		status;

	pid = 1;
	while (pid != -1)
	{
		pid = wait(&temp);
		if (WIFSIGNALED(temp))
		{
			signo = WTERMSIG(temp);
			if (signo == SIGINT)
				ft_putstr_fd("^C\n", STDERR_FILENO);
			else if (signo == SIGQUIT)
				ft_putstr_fd("^\\Quit: 3\n", STDERR_FILENO);
			g_exit_code = 128 + signo;
		}
		else
		{
			if (pid == last_pid)
			{
				status = temp;
				g_exit_code = WEXITSTATUS(status);
			}
		}
	}
	return (g_exit_code);
}

char	**keep_execve(t_data data, t_token **head, char **t, int *flag)
{
	char	**ret;

	if (!(check_command(data.path, (*head)->str)
			|| !builtin_check((*head)->str)) && *flag == 0)
	{
		printf("not working\n\n");
		exit(126);
	}
	ret = copy_orders(t);
	ret = add_order(ret, (*head)->str, *flag);
	(*head) = (*head)->next;
	*flag = 1;
	return (ret);
}

char	*find_path(char *argv[], char **envp, int i)
{
	int		k;
	char	**str;
	char	*sp_path;
	char	**temp;

	k = -1;
	while (envp[++k])
	{
		if (!ft_strncmp("PATH", envp[k], 4))
			break ;
	}
    str = ft_split(envp[k] + 5, ':');
    argv[i] = ft_strjoin("/", argv[i]);
    k = -1;
	while (str[++k])
	{
		temp = ft_split(argv[i], ' ');
		sp_path = ft_strjoin(str[k], temp[0]);
		if (access(sp_path, X_OK) == 0)
			break ;
	}
	if (access(sp_path, X_OK) == 0)
		return (sp_path);
	else
		return (0);
}


void	init_fd(t_data *data, int *io_fd)
{
	data->i_flag = 0;
	data->o_flag = 0;
	io_fd[0] = dup(0);
	io_fd[1] = dup(1);
}

void	forked_child_work(t_data *data, t_token **head, int *pipes,
		int *heredoc_count)
{
	char	**t;
	char	*cmd;
	int		io_fd[2];
	int		flag;

	flag = 0;
	t = (char **)malloc(sizeof(char *));
	t[0] = 0;
	init_fd(data, io_fd);
	while ((*head) && (*head)->str && ft_strncmp((*head)->str, "|", 1))
	{
		if (ft_strncmp((*head)->str, ">>", 2) == 0 && (*head)->type == T_REDIRECT)
			io_fd[1] = append_redirection(io_fd[1], head, data);
		else if (ft_strncmp((*head)->str, "<<", 2) == 0 && (*head)->type == T_REDIRECT)
			io_fd[0] = heredoc_redirection(io_fd[0], head, data, heredoc_count);
		else if (ft_strncmp((*head)->str, "<", 1) == 0 && (*head)->type == T_REDIRECT)
			io_fd[0] = input_redirection(io_fd[0], head, data);
		else if (ft_strncmp((*head)->str, ">", 1) == 0 && (*head)->type == T_REDIRECT)
			io_fd[1] = output_redirection(io_fd[1], head, data);
		else
			t = keep_execve(*data, head, t, &flag);
	}
	dup_pipes(head, pipes, io_fd[0], io_fd[1], data);
	if ((*head) && (*head)->next)
		(*head) = (*head)->next;
	cmd = find_path(t, data->envp, 0);
	if (check_builtin(t, *data, cmd) == -1)
		exit(1);
	if (execve(cmd, t, data->envp) == -1)
		exit(126);
}
// 만일 함수 내부에서 fd 로 묶었는데 모든 파일에 변경사항이 저장되는 현상이 발생할 경우
// 각각의 fd 값을 클로즈 해주기 위해서 fd 배열값을 가지고 가야된다.