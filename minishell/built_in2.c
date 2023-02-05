/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 20:53:24 by gyopark           #+#    #+#             */
/*   Updated: 2023/02/05 22:17:50 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**read_cmd(t_data *data, t_token **head, int flag, int *heredoc_count)
{
	char	**t;

	t = (char **)malloc(sizeof(char *));
	t[0] = 0;
	init_fd(data);
	while ((*head) && (*head)->str && ft_strncmp((*head)->str, "|", 1))
	{
		if (ft_strncmp((*head)->str, ">>", 2) == 0
			&& (*head)->type == T_REDIRECT)
			data->io_fd[1] = append_redirection(data->io_fd[1], head, data);
		else if (ft_strncmp((*head)->str, "<<", 2) == 0
			&& (*head)->type == T_REDIRECT)
			data->io_fd[0] = heredoc_redirection(data->io_fd[0], head, data, \
			heredoc_count);
		else if (ft_strncmp((*head)->str, "<", 1) == 0
			&& (*head)->type == T_REDIRECT)
			data->io_fd[0] = input_redirection(data->io_fd[0], head, data);
		else if (ft_strncmp((*head)->str, ">", 1) == 0
			&& (*head)->type == T_REDIRECT)
			data->io_fd[1] = output_redirection(data->io_fd[1], head, data);
		else
			t = keep_execve(*data, head, t, &flag);
	}
	return (t);
}
/*
void	dup_builtin_pipes(t_data *data)
{
		if (data->o_flag == 1)
			dup2(output_fd, STDOUT_FILENO);
		if (data->i_flag == 1)
			dup2(input_fd, STDIN_FILENO);
		close(output_fd);
		close(input_fd);
}
*/

/*
void	run_builtin(char **cmd, t_data data)
{
	check_builtin(cmd, data, )


}
*/
