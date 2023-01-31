/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_line2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 14:19:35 by youngski          #+#    #+#             */
/*   Updated: 2023/01/31 16:40:55 by gyopark          ###   ########.fr       */
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

void	free_orders(char **t)
{
	int	i;

	i = -1;
	while (t[++i])
		free(t[i]);
}

void	copy_make_orders(char ***t, int i)
{
	char	***ret;
	int		k;
	char	*tmp;
	int		len;

	k = -1;
	ret = (char ***)malloc(sizeof(char **) * i + 1);
	while (ret[0][++k])
	{
		len = ft_strlen(t[0][k]);
		tmp = (char *)malloc(sizeof(char) * len);
		ft_memcpy(tmp, ret[0][k], len);
		ret[0][k] = tmp;
	}
	free_orders(*t);
	t[0] = *ret;
}

int	keep_execve(t_data data, t_token **head, char ***t, int *flag)
{
	int		i;
	//첫번째 명령어를 쓸 때는 주소값 찾아서 넣어줘야된다 todo
	i = -1;
	//명령어 체킹 있는지 없는지(*head)->str
	if (!check_command(data.path, (*head)->str) && *flag == 0)
		return (-1);
	while (t[0][++i])
		;
	copy_make_orders(t, i);
	t[0][i] = (*head)->str;
	t[i + 1] = 0;
	*flag = 1;
	return (0);
}

void	forked_child_work(t_data *data, t_token **head, int *pipes,
		int *heredoc_count)
{
	char	**t;
	int		flag;
	int		output_fd;
	int		input_fd;

	t = (char **)malloc(sizeof(char *));
	t[0] = 0;
	flag = 0; // 함수 내부에서 플래그 값 1로 바꿔주고 활용할것
	while ((*head) && ft_strncmp((*head)->str, "|", 1) != 0)
	{
		if (ft_strncmp((*head)->str, "<", 1) == 0) // 문장이 < 일때
			input_fd = input_redirection(input_fd, head);
		else if (ft_strncmp((*head)->str, ">", 1) == 0) // 문장이 >일때
			output_fd = output_redirection(output_fd, head);
		else if (ft_strncmp((*head)->str, ">>", 2) == 0)
			input_fd = append_redirection(output_fd, head);
		else if (ft_strncmp((*head)->str, "<<", 2 == 0))
			input_fd = heredoc_redirection(input_fd, head, data, heredoc_count);
		else
			if (keep_execve(*data, head, &t, &flag) == -1)
				return ;
	}
	dup_pipes(head, pipes, input_fd, output_fd);
	(*head) = (*head)->next;
	execve(t[0], t, data->envp);
}
// 만일 함수 내부에서 fd 로 묶었는데 모든 파일에 변경사항이 저장되는 현상이 발생할 경우
	// 각각의 fd 값을 클로즈 해주기 위해서 fd 배열값을 가지고 가야된다.
