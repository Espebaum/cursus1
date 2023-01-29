/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 14:19:35 by youngski          #+#    #+#             */
/*   Updated: 2023/01/29 21:37:37 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	init_fork(t_token *head, char **envp, t_data data, int i)
{
	int	pipes[2];

	pipe(pipes);
	if (pipes[0] == -1 || pipes[1] == -1)
		return (1);
	data.pid[i] = fork();
	if (data.pid[i] == -1)
		return (1);
	else if (data.pid[i] == 0)
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
	return (0);
}

int	init_data(t_data *data, int *count)
{
	data->doc_count = 0;
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
	}
	return (0);
}

//count 는 갯수를 1부터 세는것
int	*pipe_line(int *count, t_token *head, char **envp)
{
	int		i;
	t_data	data;
	int		doc_count;

	i = -1;
	doc_count = 0;
	init_data(&data, count);
	if (count[1] != 0)
		run_heredoc(count[1], head, &data);
	while (++i < count[0])
	{
		//위에서 히어독을 하나씩 받아서 파일을 만들어두는 작업을 한번에 진행하였다
		//아래에서 각각의 자식들이 히어독인지를 체크하여서 히어독일 경우 아까 만들어둔 파일명(data->doc_name)
		//을 통해 오픈을 진행해서 각각 히어독을 통해 작업을 진행한다.
		//1. 히어독일 때 포크를 만든다.
		//2. 히어독이 아닐 때 포크를 만든다.
		if (check_heredoc(head))
		{
			doc_count++;
			data.doc_count = doc_count;
		}
		else
		{
			init_fork(head, envp, data, i);
			//fd 파이프 안열렸을 때 문제 에러 처리 할것 todo
		}
	}
	i = -1;
	waitpid(data.pid[count[0] - 1], NULL, 0);
	while (++i < count[0] -1)
		wait(0);
	return (free_pid_docs(data.pid, data.doc_fd));
}
