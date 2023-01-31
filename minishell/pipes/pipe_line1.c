/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_line1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 14:19:35 by youngski          #+#    #+#             */
/*   Updated: 2023/01/31 22:57:03 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	do_heredoc(t_token *head, t_data *data, int count)
{
	int		i;
	int		k;
	char	*t;
	char	*limiter;
	int		*doc_index;

	i = -1;
	k = 0;
	t = ".here_doc";
	doc_index = find_heredoc_index(head, count);
	while (++i < count)
	{
		if (access(t, F_OK) == 0)
			open_doc_file(data, t, &i, &k);
		else
		{
			t = ft_strjoin(t, "1");
			continue ;
		}
		limiter = get_limiter(head, doc_index[i]);
		heredoc_file_make(doc_index[i], data->doc_fd[i], limiter);
	}
	close_all_opend_heredoc_fd(data, count);//열었던 쓰기전용 모든 fd 닫아주기
}

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
	}
	set_signal(IGN, IGN);
	parent_proc(pipes);
	return (data->pid[i]);
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

int	pipe_line(int *count, t_token *head, char **envp)
{
	int		i;
	t_data	data;
	int		here_doc_count;

	data.original_fd[0] = dup(0);
	data.original_fd[1] = dup(1);
	here_doc_count = 0;
	i = -1;
	init_data(&data, count, envp);
	if (count[1] != 0)
		do_heredoc(head, &data, count[1]);
	while (++i < count[0] + 1)
	{
		data.pid[i] = init_fork(&head, &data, i, &here_doc_count);
		// fd 파이프 안열렸을 때 문제 에러 처리 할것 todo
	}
	// i = -1;
	// g_exit_code = waitpid(data.pid[count[0] - 1], NULL, 0);
	// while (++i < count[0] - 1)
	// 	wait(0);
	//free_pid_docs(data.pid, data.doc_fd);
	return (wait_all(data, data.pid[i]));
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