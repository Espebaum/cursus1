/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 14:19:35 by youngski          #+#    #+#             */
/*   Updated: 2023/01/30 22:39:01 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	free_pid_docs(int *pid, int *doc_fd)
{
	free(pid);
	if (doc_fd)
		free(doc_fd);
	return (0);
}

int	init_data(t_data *data, int *count, char **envp)
{
	data->path = get_path(envp);
	data->envp = envp;
	data->doc_count = 0;
	data->doc_fd = 0;
	data->pid = (int *)malloc(sizeof(int) * count[0]);
	if (!(data->pid))
		return (1);
	if (count[1] != 0)
	{
		data->doc_fd = (int *)malloc(sizeof(int) * count[1]);
		if (!(data->doc_fd))
			return (1);
	}
	return (0);
}
// count[0] 파이프('|') 갯수, count[1] 리다이렉션('<<') 갯수
// 구조제 t_data 일람
// typedef struct s_data
// {
// 	int		*pid; -> pid 배열
// 	int		*doc_fd; -> heredoc 파일 fd 배열
// 	char	**doc_name; -> heredoc 파일 이름 배열
// 	int		doc_count; -> heredoc 개수
// }	t_data;

//count 는 갯수를 1부터 세는것
int	*pipe_line(int *count, t_token *head, char **envp)
{
	int		i;
	t_data	data;
	int		here_doc_count;

	here_doc_count = 0;
	i = -1;
	init_data(&data, count, envp);
	if (count[1] != 0)
		get_heredoc(head, &data, count[1]);
	while (++i < count[0] + 1)
	{
		init_fork(head, data, i, &here_doc_count);
		// fd 파이프 안열렸을 때 문제 에러 처리 할것 todo
	}
	i = -1;
	waitpid(data.pid[count[0] - 1], NULL, 0);
	while (++i < count[0] - 1)
		wait(0);
	pid_free(data.pid);
	return (free_pid_docs(data.pid, data.doc_fd));
}
