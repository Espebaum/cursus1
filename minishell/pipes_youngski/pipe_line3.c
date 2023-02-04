/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_line3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 14:19:35 by youngski          #+#    #+#             */
/*   Updated: 2023/02/04 14:58:18 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	dup_pipes(t_token **head, int *pipes, int input_fd, int output_fd, t_data *data)
{
	if ((*head))
	{
		if (data->o_flag == 0)
			dup2(pipes[1], STDOUT_FILENO);
		//if (data->i_flag == 0)
		//	dup2(pipes[0], STDIN_FILENO);
		close(pipes[0]);
		close(pipes[1]);
	}
	else
	{
		if (data->o_flag == 1)
			dup2(output_fd, STDOUT_FILENO);
		if (data->i_flag == 1)
			dup2(input_fd, STDIN_FILENO);
		close(output_fd);
		close(input_fd);
	}
}

int	output_redirection(int output_fd, t_token **head, t_data *data)
{
	int		fd;

	close(output_fd);
	(*head) = (*head)->next;
	fd = open((*head)->str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	(*head) = (*head)->next;
	data->o_flag = 1;
	return (fd);
}

int	input_redirection(int input_fd, t_token **head, t_data *data)
{
	int		fd;

	close(input_fd);
	(*head) = (*head)->next;
	fd = open ((*head)->str, O_RDONLY);
	(*head) = (*head)->next;
	data->i_flag = 1;
	return (fd);
}

int	append_redirection(int output_fd, t_token **head, t_data *data)
{
	int		fd;

	close(output_fd);
	(*head) = (*head)->next;
	fd = open ((*head)->str, O_WRONLY | O_CREAT | O_APPEND, 0644);
	(*head) = (*head)->next;
	data->o_flag = 1;
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
	data->i_flag = 1;
	return (fd);
}
