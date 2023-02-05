/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 20:53:24 by gyopark           #+#    #+#             */
/*   Updated: 2023/02/05 20:59:33 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**read_cmd(t_data *data, t_token *head)

	flag = 0;
	t = (char **)malloc(sizeof(char *));
	t[0] = 0;
	init_fd(data, io_fd);
	while ((*head) && (*head)->str && ft_strncmp((*head)->str, "|", 1))
	{
		if (ft_strncmp((*head)->str, ">>", 2) == 0 && (*head)->type == T_REDIRECT)
			io_fd[1] = append_redirection(io_fd[1], head, data);
		else if (ft_strncmp((*head)->str, "<<", 2) == 0 && (*head)->type == T_REDIRECT)
			io_fd[0] = heredoc_redirection(io_fd[0], head, data, heredoc_count);
		else if (ft_strncmp((*head)->str, "<", 1) == 0 && (*head)->type == T_REDIRECT)
			io_fd[0] = input_redirection(io_fd[0], head, data);
		else if (ft_strncmp((*head)->str, ">", 1) == 0 && (*head)->type == T_REDIRECT)
			io_fd[1] = output_redirection(io_fd[1], head, data);
		else
			t = keep_execve(*data, head, t, &flag);
	}