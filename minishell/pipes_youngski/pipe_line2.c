/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_line2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 14:19:35 by youngski          #+#    #+#             */
/*   Updated: 2023/02/03 22:39:12 by gyopark          ###   ########.fr       */
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

char	**keep_execve(t_data data, t_token **head,char **t, int *check, int *flag)
{
	char **ret;
	//첫번째 명령어를 쓸 때는 주소값 찾아서 넣어줘야된다 todo
	//명령어 체킹 있는지 없는지(*head)->str
	if (check_command(data.path, (*head)->str) && *flag == 0)
	{
		*check = -1;
		return NULL;
	}
	ret = copy_orders(t);
	ret = add_order(ret, (*head)->str, *flag);
	(*head) = (*head)->next;
	*flag = 1;
	*check = 0;
	return (ret);
}

char	*find_path(char *argv[], char **envp, int i)
{
    int		k;
    char	**str;
    char	*sp_path;
    char		**temp;

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

void	forked_child_work(t_data *data, t_token **head, int *pipes,
		int *heredoc_count)
{
	char	**t;
	int		flag;
	int		output_fd;
	int		input_fd;
	int		check;

	t = (char **)malloc(sizeof(char *));
	t[0] = 0;
	flag = 0; // 함수 내부에서 플래그 값 1로 바꿔주고 활용할것
	input_fd = dup(0);
	output_fd = dup(1);
	while ((*head) && (*head)->str && ft_strncmp((*head)->str, "|", 1) != 0)
	{
		if (ft_strncmp((*head)->str, ">>", 2) == 0)
		{
			//printf("append\n\n");
			output_fd = append_redirection(output_fd, head);
			//printf("make ifd : %d\n", input_fd);
		}
		else if (ft_strncmp((*head)->str, "<<", 2) == 0)
			input_fd = heredoc_redirection(input_fd, head, data, heredoc_count);
		else if (ft_strncmp((*head)->str, "<", 1) == 0) // 문장이 < 일때
			input_fd = input_redirection(input_fd, head);
		else if (ft_strncmp((*head)->str, ">", 1) == 0) // 문장이 >일때
			output_fd = output_redirection(output_fd, head);
		else
		{
			t = keep_execve(*data, head, t, &check, &flag);
			if (check == -1)
				return ;
		}
		if ((*head) && ft_strncmp((*head)->str, "|", 1) == 0)
			break ;
	}
	//printf("fin ifd : %d\n", input_fd);
	dup_pipes(head, pipes, input_fd, output_fd);
	if ((*head) && (*head)->next)
		(*head) = (*head)->next;
	char *asdf = find_path(t, data->envp, 0);
	//printf("cmd[0] : %s\n\n", asdf);
	//printf("t[0] : %s, t[1] : %s, t[2] : %s\n\n", t[0], t[1], t[2]);
	execve(asdf, t, data->envp);
}
// 만일 함수 내부에서 fd 로 묶었는데 모든 파일에 변경사항이 저장되는 현상이 발생할 경우
// 각각의 fd 값을 클로즈 해주기 위해서 fd 배열값을 가지고 가야된다.