/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_line1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark < gyopark@student.42seoul.kr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 14:19:35 by youngski          #+#    #+#             */
/*   Updated: 2023/02/13 22:32:46 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	parent_proc(int *pipes)
{
	dup2(pipes[0], STDIN_FILENO);
	close(pipes[0]);
	close(pipes[1]);
}

int	init_fork(t_tuple tup, int i, int *heredoc_count, t_list *env_head)
{
	int		pipes[2];
	t_token	**head;
	t_data	*data;

	head = tup.head;
	data = tup.data;
	if (pipe(pipes) == -1)
		exit_error("pipe error", 0, 1);
	set_signal(DFL, DFL);
	data->pid[i] = fork();
	if (data->pid[i] == -1)
		exit_error("fork error", 0, 1);
	else if (data->pid[i] == 0)
		forked_child_work(tup, pipes, heredoc_count, env_head);
	set_signal(IGN, IGN);
	while ((*head) && (*head)->type != T_PIPE)
		(*head) = (*head)->next;
	if ((*head))
		(*head) = (*head)->next;
	parent_proc(pipes);
	return (data->pid[i]);
}

int	pipe_line(t_data data, t_token *head, t_cover cover, t_list *env_head)
{
	t_token	*temp;
	pid_t	pid;
	int		i;
	int		here_doc_count;
	t_tuple	tuple_td;

	temp = head->next;
	tuple_td.head = &temp;
	tuple_td.data = &data;
	here_doc_count = 0;
	i = -1;
	while (++i < head->cmds)
	{
		pid = init_fork(tuple_td, i, &here_doc_count, env_head);
	}
	free(data.pid);
	dup2(cover.cp_stdin, STDIN_FILENO);
	close(data.io_fd[0]);
	close(data.io_fd[1]);
	return (wait_all(pid));
}
