/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_line_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 14:19:35 by youngski          #+#    #+#             */
/*   Updated: 2023/01/30 22:53:37 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int output_redirection(t_token **head)
{
    int     fd;

    (*head) = (*head)->next;
    fd = open((*head)->str, O_WRONLY, O_TRUNC);
    (*head) = (*head)->next;
    return fd;
}

int input_redirection(t_token **head)
{
    int     fd;

    (*head) = (*head)->next;
    fd = open ((*head)->str, O_RDONLY);
    (*head) = (*head)->next;
    return fd;
}

int append_redirection(t_token **head)
{
    int     fd;

    (*head) = (*head)->next;
    fd = open ((*head)->str, O_WRONLY, O_APPEND);
    (*head) = (*head)->next;
    return fd;
}

int heredoc_redirection(t_token **head, t_data *data, int *heredoc_count)
{
    char    *t;
    int     fd;

    (*head) = (*head)->next;
    t = data->doc_name[(*heredoc_count)++];
    fd = open (t,O_RDONLY);
    (*head) = (*head)->next;
    return (fd);
}

void    free_orders(char **t)
{
    int i;

    i = -1;
    while (t[++i])
        free(t[i]);
}

void    copy_make_orders(char ***t, int i)
{
    char    ***ret;
    int     k;
    char    *tmp;
    int     len;
    
    k = -1;
    ret = (char ***)malloc(sizeof(char **) * i + 1);
    while (ret[0][++k])
    {
        len = ft_strlen(t[0][k]);
        tmp = (char *)malloc(sizeof(char) * len);
        ft_memcpy(tmp, ret[0][k], len);
        ret[0][k] = tmp;
    }
    free_orders(**t);
    t[0] == **ret;
}

int keep_execve(t_data data, t_token **head, char ***t, int flag)
{
    char    *ret;
    int     i;
//첫번째 명령어를 쓸 때는 주소값 찾아서 넣어줘야된다 todo
    i = -1;
    //명령어 체킹 있는지 없는지(*head)->str
    if (!check_command(data.path, (*head)->str) && flag == 0)
        return (-1);
    while (t[0][++i])
        ;
    copy_make_orders(t, i);
    t[0][i] = (*head)->str;
    t[i + 1] = 0;
    return (0);
}

void	forked_child_work(t_data *data, t_token **head, int *pipes, int *heredoc_count)
{
    char    **t;
    int     flag;
    int     output_fd;
    int     input_fd;
    int     check;

    flag = 0;
    check = 1;
    t = (char **)malloc(sizeof(char *));
    t[0] = 0;
// 만일 함수 내부에서 fd 로 묶었는데 모든 파일에 변경사항이 저장되는 현상이 발생할 경우
// 각각의 fd 값을 클로즈 해주기 위해서 fd 배열값을 가지고 가야된다.
    flag = 0; // 함수 내부에서 플래그 값 1로 바꿔주고 활용할것
    t = 0;
    while ((*head) && ft_strncmp((*head)->str, "|", 1) != 0)
    {
        if (ft_strncmp((*head)->str, "<", 1) == 0) // 문장이 < 일때
        {
            close(input_fd);
            input_fd = input_redirection(head);
        }
        else if (ft_strncmp((*head)->str, ">", 1) == 0) // 문장이 >일때
        {
            close(output_fd);
            output_fd = output_redirection(head);
        }
        else if (ft_strncmp((*head)->str, ">>", 2) == 0)
        {
            close(output_fd);
            input_fd = append_redirection(head);
        }
        else if (ft_strncmp((*head)->str, "<<",2 == 0))
        {
            close(input_fd);
            input_fd = heredoc_redirection(head, data, heredoc_count);
        }
        else
        {
            check = keep_execve(*data, pipes, &t, flag);
            if (flag == 0 && check == -1)
                return ;
            flag = 1;
        }
    }
    if ((*head))
    {
        dup2(pipes[0], 0);
        dup2(pipes[1], 1);
    }
    else
    {
        dup2(output_fd, STDOUT_FILENO);
        dup2(input_fd, STDIN_FILENO);
    }
    (*head) = (*head)->next;
    execve(t[0], t, data->envp);
}

void	init_fork(t_token **head, t_data *data, int i, int *heredoc_count)
{
	int	pipes[2];

	if (pipe(pipes) == -1)
		return (0);
	data->pid[i] = fork();
	if (data->pid[i] == -1)
		return (0);
	else if (data->pid[i] == 0)
	{
		forked_child_work(data, pipes, head, heredoc_count);
	}
	dup2(pipes[0], STDIN_FILENO);
	close(pipes[0]);
	close(pipes[1]);
	return (1);
}
