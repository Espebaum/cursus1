/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_line2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 14:19:35 by youngski          #+#    #+#             */
/*   Updated: 2023/02/06 21:26:46 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	wait_all(pid_t last_pid)
{
	pid_t	pid;
	int		temp;
	int		signo;
	int		status;
	int		i;

	pid = 1;
	i = 0;
	while (pid != -1)
	{
		pid = wait(&temp);
		if (WIFSIGNALED(temp))
		{
			signo = WTERMSIG(temp);
			if (signo == SIGINT && i++ == 0)
				printf("\n");
			if (signo == SIGQUIT && i++ == 0)
				printf("Quit: 3\n");
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
	char	*cmd;

	cmd = (*head)->str;
	if (cmd[0] == '\0' || (!(check_command(data.path, cmd) || !builtin_check(cmd)) && *flag == 0))
		exit_error(cmd, 0, 127);
	ret = copy_orders(t);
	ret = add_order(ret, cmd, *flag);
	(*head) = (*head)->next;
	*flag = 1;
	return (ret);
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
	if (check_builtin(t, *data, cmd) == -1)
		exit(1);
	if (execve(cmd, t, data->envp) == -1)
		exit(126);
}
// 만일 함수 내부에서 fd 로 묶었는데 모든 파일에 변경사항이 저장되는 현상이 발생할 경우
// 각각의 fd 값을 클로즈 해주기 위해서 fd 배열값을 가지고 가야된다.