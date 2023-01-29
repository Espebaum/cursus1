/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngski <youngski@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 14:19:35 by youngski          #+#    #+#             */
/*   Updated: 2023/01/29 17:47:20 by youngski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe_line.h"

int	init_fork(t_token *head, char **envp, int number)
{
	int	pipes[2];

	pipe(pipes);
	if (pipes[0] == -1 || pipes[1] == -1)
		return (1);
	pid[i] = fork();
	if (pid[i] == -1)
		return (1);
	else if (pid[i] == 0)
		child_work(head, pipes, envp);
	else
	{
		dup2(pipes[0], 0);
		close(pipes[0]);
		close(pipes[1]);
	}
	return (0);
}

int	free_pid_docs(int *pid, int *doc_fd)
{
	free(pid);
	if (doc_fd)
		free(doc_fd);
	return (0)
}

int	init_data(t_data *data, int *count)
{
	data->count = 0;
	data->pid = 0;
	data->doc_fd = 0;
	data->pid = (int *)malloc(sizeof(int) * count[0]);
	if (!(data->pid))
		return (1);
	if (count[1] != 0)
	{
		data->doc_fd = (int *)malloc(sizeof(int) * count[1]);
		if (!(data->doc_fd))
			return (1);
		make_doc_fd(count[1], doc_fd);
	}
	return (0);
}

//count 는 갯수를 1부터 세는것
int	*pipe_line(int *count, t_token *head, char **envp)
{
	int	i;
	t_data data;
	int	doc_count;

	i = -1;
	doc_count = 0;
	init_data(&data, count);
	run_heredoc(count[1], &head);
	while (++i < count[0])
	{
		if (check_heredoc(head))
			doc_count++;
		data->doc_count = doc_count;
		if (init_fork(head, envp, data, i))
			continue ;//fd 파이프 안열렸을 때 문제 에러 처리 할것 todo
	}
	i = -1;
	waitpid(pid[count[0] - 1], null, 0);
	while (++i < count[0] -1)
		wait(0);
	return (free_pid_docs(pid, doc_fd));
}
