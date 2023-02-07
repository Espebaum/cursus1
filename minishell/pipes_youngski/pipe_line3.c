/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_line3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 14:19:35 by youngski          #+#    #+#             */
/*   Updated: 2023/02/06 22:08:15 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	dup_pipes(t_token **head, int *pipes, t_data *data)
{
	if ((*head))
	{
		if (data->o_flag == 0)
			dup2(pipes[1], STDOUT_FILENO);
		if (data->o_flag == 1)
			dup2(data->io_fd[1], STDOUT_FILENO);
		if (data->i_flag == 1)
			dup2(data->io_fd[0], STDIN_FILENO);
		close(data->io_fd[0]);
		close(pipes[0]);
		close(pipes[1]);
	}
	else
	{
		if (data->o_flag == 1)
			dup2(data->io_fd[1], STDOUT_FILENO);
		if (data->i_flag == 1)
			dup2(data->io_fd[0], STDIN_FILENO);
		close(data->io_fd[1]);
		close(data->io_fd[0]);
	}
}

int	output_redirection(int output_fd, t_token **head, t_data *data)
{
	int		fd;
	char	*filename;

	close(output_fd);
	(*head) = (*head)->next;
	filename = (*head)->str;
	fd = open((*head)->str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		exit_error((*head)->str, 0, 1);
	(*head) = (*head)->next;
	data->o_flag = 1;
	return (fd);
}

int	input_redirection(int input_fd, t_token **head, t_data *data)
{
	int		fd;
	char	*filename;

	close(input_fd);
	(*head) = (*head)->next;
	filename = (*head)->str;
	fd = open (filename, O_RDONLY);
	if (fd == -1)
		exit_error(filename, 0, 1);
	(*head) = (*head)->next;
	data->i_flag = 1;
	return (fd);
}

int	append_redirection(int output_fd, t_token **head, t_data *data)
{
	int		fd;
	char	*filename;

	close(output_fd);
	(*head) = (*head)->next;
	filename = (*head)->str;
	fd = open ((*head)->str, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		exit_error(filename, 0, 1);
	(*head) = (*head)->next;
	data->o_flag = 1;
	return (fd);
}

int	heredoc_redirection(int input_fd, t_token **head, t_data *data,
		int *heredoc_count)
{
	char	*filename;
	int		fd;

	close(input_fd);
	(*head) = (*head)->next;
	filename = data->doc_name[(*heredoc_count)++];
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		exit_error(filename, 0, 1);
	(*head) = (*head)->next;
	data->i_flag = 1;
	return (fd);
}
