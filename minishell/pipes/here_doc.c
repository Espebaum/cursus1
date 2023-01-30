/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 16:03:57 by youngski          #+#    #+#             */
/*   Updated: 2023/01/30 21:54:07 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_heredoc(t_token *head)
{
	int	flag;

	flag = 0;
	while (head || ft_strcmp(head->str, "<<", 2) != 0)
	{
		head = (head->next);
		if (!ft_strcmp(head->str, "<<", 2) || !ft_strcmp(head->str, "|", 1))
		{
			flag = !(ft_strcmp(head->str, "<<", 2));
			break ;
		}
	}
	if (flag == 1)
		return (1);
	else
		return (0);
}

void	heredoc_file_make(int doc_index, int doc_fd, char *limiter)// t_data data (data->doc_fd), i, *doc_index
{
	char	*line;

	while (1)
	{
		write(1, "heredoc> ", 9);
		line = readline("");
		if (!line || ft_strncmp(line, limiter, ft_strlen(line)) == 0)
		{
			free(line);
			break ;
		}
		write(doc_fd, line, ft_strlen(line));
		free(line);
	}
}

char	*get_limiter(t_token *head, int doc_index)
{
	char	*limiter;
	char	*limiter_line;

	while (doc_index--)
		head = head->next;
	limiter = ft_strdup(head->str);
	limiter_line = ft_strjoin(limiter, "\n");
	free(limiter);
	return (limiter_line);
}

int	*find_heredoc_index(t_token *head, int count)
{
	t_token	*temp;
	int		*doc_index;
	int		doc_idx;
	int		k;
	int		token_len;

	token_len = 0;
	temp = head;
	while (temp->next)
		token_len++;
	k = 0;
	doc_idx = 0;
	doc_index = (int *)malloc(sizeof(int) * count);
	if (!doc_index)
		return (0);
	while (doc_idx < token_len)
	{
		while (ft_strcmp(head->str, "<<", 2) != 0 || head)
		{
			head = head->next;
			doc_idx++;
		}
		doc_index[k++] = doc_idx++;
		head->next;
	}
	return (doc_index);
}

void	get_heredoc(t_token *head, t_data *data, int count)
{
	int		i;
	int		k;
	char	*t;
	char	*limiter;
	int		*doc_index;

	i = 0;
	k = 0;
	t = ".here_doc";
	doc_index = find_heredoc_index(head, count);
	while (i < count)
	{
		if (access(t, F_OK) != 0)
		{
			data->doc_fd[i] = open(t, O_WRONLY | O_CREAT, 0644);
			data->doc_name[k++] = t;
		}
		else
		{
			t = ft_strjoin(t, "1");
			continue ;
		}
		limiter = get_limiter(head, doc_index[i]);
		heredoc_file_make(doc_index[i], data->doc_fd[i], limiter);
		i++;
	}
	closeall_fds();//열었던 쓰기전용 모든 fd 닫아주기
}
