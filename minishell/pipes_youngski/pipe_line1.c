/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_line1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 14:19:35 by youngski          #+#    #+#             */
/*   Updated: 2023/02/10 17:21:12 by gyopark          ###   ########.fr       */
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
		exit_error("pipe error", 0, 1);
	set_signal(DFL, DFL);
	data->pid[i] = fork();
	if (data->pid[i] == -1)
		exit_error("fork error", 0, 1);
	else if (data->pid[i] == 0)
		forked_child_work(data, head, pipes, heredoc_count);
	set_signal(IGN, IGN);
	while ((*head) && (*head)->type != T_PIPE)
		(*head) = (*head)->next;
	if ((*head))
		(*head) = (*head)->next;
	parent_proc(pipes);
	return (data->pid[i]);
}

int	pipe_line(t_data data, t_token *head, t_cover cover)
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
	free(data.pid);
	dup2(cover.cp_stdin, STDIN_FILENO);
	return (wait_all(pid));
}
