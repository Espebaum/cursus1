/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 16:03:57 by youngski          #+#    #+#             */
/*   Updated: 2023/01/31 15:32:30 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	free_pid_docs(int *pid, int *doc_fd)
{
	free(pid);
	if (doc_fd)
		free(doc_fd);
	return (0);
}

void	open_doc_file(t_data *data, char *t, int *i, int *k)
{
	data->doc_fd[*i] = open(t, O_WRONLY | O_CREAT, 0644);
	data->doc_name[(*k)++] = t;
}