/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_line1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 14:19:35 by youngski          #+#    #+#             */
/*   Updated: 2023/02/03 21:11:27 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	parent_proc(int *pipes)
{
	dup2(pipes[0], STDIN_FILENO);
	close(pipes[0]);
	close(pipes[1]);
}

int	init_fork(t_token **head, t_data *data, int i, int *heredoc_count)
{
	int	pipes[2];

	if (pipe(pipes) == -1)
		return (0);
	set_signal(DFL, DFL);
	data->pid[i] = fork();
	if (data->pid[i] == -1)
		return (0);
	else if (data->pid[i] == 0)
	{
		forked_child_work(data, head, pipes, heredoc_count);
		exit(1);
	}
	while ((*head) && (*head)->type != T_PIPE)
		(*head) = (*head)->next;
	set_signal(IGN, IGN);
	parent_proc(pipes);
	return (data->pid[i]);
}

int	init_data(t_data *data, t_doc doc, char **envp, t_token *head)
{
	data->path = get_path(envp);
	data->envp = envp;
	data->pid = (int *)malloc(sizeof(int) * head->cmds);
	if (!(data->pid))
		return (1);
	data->doc_name = doc.name;
	return (0);
}

int	pipe_line(t_data data, t_token *head, int cp_stdin)
{
	t_token	*temp;
	pid_t	pid;
	int		i;
	int		here_doc_count;

	temp = head->next;
	here_doc_count = 0;
	i = -1;
	while (++i < head->cmds)
	{
		pid = init_fork(&temp, &data, i, &here_doc_count);
	}
	// i = -1;
	// g_exit_code = waitpid(data.pid[count[0] - 1], NULL, 0);
	// while (++i < count[0] - 1)
	// 	wait(0);
	free(data.pid);
	dup2(cp_stdin, STDIN_FILENO);
	//free_pid_docs(data.pid, data.doc_fd);
	return (wait_all(pid));
	//return (g_exit_code);
}
// count[0] 파이프('|') 갯수, count[1] 리다이렉션('<<') 갯수
// 구조제 t_data 일람
// typedef struct s_data
// {
// 	int		*pid; -> pid 배열
// 	int		*doc_fd; -> heredoc 파일 fd 배열
// 	char	**doc_name; -> heredoc 파일 이름 배열
// 	int		doc_count; -> heredoc 개수
//	char	**envp;
//	char	**path;
// }	t_data;
