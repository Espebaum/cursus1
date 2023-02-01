/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_line2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 14:19:35 by youngski          #+#    #+#             */
/*   Updated: 2023/02/01 14:59:07 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	wait_all(t_data data, pid_t last_pid)
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
	free(data.pid);
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

// char	**keep_execve(t_data data, t_token **head, int *flag)
// {
// 	char	**temp;

// 	temp = (char **)malloc(sizeof(char *) * (*flag + 1));
// 	if (check_command(data.path, (*head)->str))
// 	{
// 		free(temp);
// 		*flag = -1;
// 		return (NULL);
// 	}
// 	else
// 		temp[*flag] = (*head)->str;
// 	*head = (*head)->next;
// 	return (temp);
// }

void append_last(char *str, char ***t)
{
    char **temp;
    char *str_temp;
    int i;
    int k;
    int j;

    i = 0;
    j = 0;
    k = 0;
    temp = *t;
    while (temp[i])
        i++;
    while (str[k])
        k++;
    str_temp = (char *)malloc(sizeof(char) * k);
    while (str[j])
    {
        str_temp[j] = str[j];
        j++;
    }
    str_temp[j] = 0;
    temp[i] = str_temp;
}

void deep_copy(char ***t , char ***str, int i, int k)
{
    char **temp;
    char **ret;

    temp = *str;
    while (temp[i])
        i++;
    printf("%d", i);
    ret = (char **)malloc(sizeof(char *) * i + 1);
    ret[i] = 0;
    i = -1;
    while (temp[++i])
    {
        k = 0;
        while (temp[i][k])
            k++;
        ret[i] = (char *)malloc(sizeof(char) * k + 1);
        ret[i][k] = 0;
        k = -1;
        while (temp[i][++k])
        {
            ret[i][k] = temp[i][k];
        }
    }
    *t = ret;
}

 int	keep_execve(t_data data, t_token **head, char ***t, int *flag)
 {
 	int		i;
	char 	***temp;

 	i = -1;

 	if (check_command(data.path, (*head)->str) && *flag == 0)
 		return (-1);
	temp = (char ***)malloc(sizeof(char **));	
	deep_copy(temp, t, 0, 0);
	append_last((*head)->str, t);
 	// t[0][i] = (*head)->str;
 	// t[i + 1] = 0;
 	// *flag = 1;
 	(*head) = (*head)->next;
	return (0);
 }

void	forked_child_work(t_data *data, t_token **head, int *pipes,
		int *heredoc_count)
{
	char	**t;
	//char	**cmd;
	int		flag;
	int		output_fd;
	int		input_fd;
	char	*path_cmd;
	
	t = (char **)malloc(sizeof(char *));
	//cmd = NULL;
	flag = 0; // 함수 내부에서 플래그 값 1로 바꿔주고 활용할것
	(*head) = (*head)->next;
	while ((*head) && ft_strncmp((*head)->str, "|", 1) != 0)
	{
		printf("asdfasdfasdf\n\n\n");
		if (ft_strncmp((*head)->str, "<", 1) == 0) // 문장이 < 일때
			input_fd = input_redirection(input_fd, head);
		else if (ft_strncmp((*head)->str, ">", 1) == 0) // 문장이 >일때
			output_fd = output_redirection(output_fd, head);
		else if (ft_strncmp((*head)->str, ">>", 2) == 0)
			input_fd = append_redirection(output_fd, head);
		else if (ft_strncmp((*head)->str, "<<", 2 == 0))
			input_fd = heredoc_redirection(input_fd, head, data, heredoc_count);
		else
		{
			//cmd = keep_execve(*data, head, (&flag));
			// if (flag == -1)
			// 	ft_perror("cannot find command", 127);
			//flag++;
			//cmd[flag] = NULL;
			if (keep_execve(*data, head, &t, &flag) == -1)
			{
				printf("asdfasdfasdf\n\n\n");
				return ;
			}
		}
	}
	write(1, t[0], ft_strlen(t[0]));
	write(1, "\n", 1);
	(void)pipes;
	//dup_pipes(head, pipes, data);
	(*head) = (*head)->next;
	path_cmd = check_command(data->path, t[0]);
	//execve(t[0], t, data->envp);
	execve(path_cmd, t, data->envp);
}
// 만일 함수 내부에서 fd 로 묶었는데 모든 파일에 변경사항이 저장되는 현상이 발생할 경우
	// 각각의 fd 값을 클로즈 해주기 위해서 fd 배열값을 가지고 가야된다.
// void	forked_child_work(t_data *data, t_token **head, int *pipes,
// 		int *heredoc_count)
// {
// 	char	**t;
// 	int		flag;
// 	int		output_fd;
// 	int		input_fd;

// 	t = (char **)malloc(sizeof(char *));
// 	t[0] = 0;
// 	flag = 0; // 함수 내부에서 플래그 값 1로 바꿔주고 활용할것
// 	(*head) = (*head)->next;
// 	while ((*head) && ft_strncmp((*head)->str, "|", 1) != 0)
// 	{
// 		if (ft_strncmp((*head)->str, "<", 1) == 0) // 문장이 < 일때
// 			input_fd = input_redirection(input_fd, head);
// 		else if (ft_strncmp((*head)->str, ">", 1) == 0) // 문장이 >일때
// 			output_fd = output_redirection(output_fd, head);
// 		else if (ft_strncmp((*head)->str, ">>", 2) == 0)
// 			input_fd = append_redirection(output_fd, head);
// 		else if (ft_strncmp((*head)->str, "<<", 2 == 0))
// 			input_fd = heredoc_redirection(input_fd, head, data, heredoc_count);
// 		else
// 		{
// 			if (keep_execve(*data, head, &t, &flag) == -1)
// 				return ;
// 		}
// 	}
// 	printf("a\n");
// 	dup_pipes(head, pipes, input_fd, output_fd);
// 	(*head) = (*head)->next;
// 	execve(t[0], t, data->envp);
// }
