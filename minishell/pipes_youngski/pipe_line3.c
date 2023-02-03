/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_line3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 14:19:35 by youngski          #+#    #+#             */
/*   Updated: 2023/02/03 22:42:58 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	dup_pipes(t_token **head, int *pipes, int input_fd, int output_fd)
{
	if ((*head))
	{
		dup2(pipes[0], STDIN_FILENO);
		dup2(pipes[1], STDOUT_FILENO);
		close(pipes[0]);
	}
	else
	{
		dup2(output_fd, STDOUT_FILENO);
		dup2(input_fd, STDIN_FILENO);
		close(input_fd);
	}
}

int	output_redirection(int output_fd, t_token **head)
{
	int		fd;

	close(output_fd);
	(*head) = (*head)->next;
	fd = open((*head)->str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	(*head) = (*head)->next;
	return (fd);
}

int	input_redirection(int input_fd, t_token **head)
{
	int		fd;

	close(input_fd);
	(*head) = (*head)->next;
	fd = open ((*head)->str, O_RDONLY);
	(*head) = (*head)->next;
	return (fd);
}

int	append_redirection(int output_fd, t_token **head)
{
	int		fd;

	close(output_fd);
	(*head) = (*head)->next;
	fd = open ((*head)->str, O_WRONLY | O_CREAT | O_APPEND, 0644);
	(*head) = (*head)->next;
	return (fd);
}

int	heredoc_redirection(int input_fd, t_token **head, t_data *data,
		int *heredoc_count)
{
	char	*t;
	int		fd;

	close(input_fd);
	(*head) = (*head)->next;
	t = data->doc_name[(*heredoc_count)++];
	fd = open(t, O_RDONLY);
	(*head) = (*head)->next;
	return (fd);
}