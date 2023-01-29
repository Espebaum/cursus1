/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 16:03:57 by youngski          #+#    #+#             */
/*   Updated: 2023/01/29 21:38:01 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	*find_heredoc_index(t_token *head, int count)
{
	int	*doc_index;
	int	doc_idx;
	int	k;

	k = 0;
	doc_idx = 0;
	doc_index = (int *)malloc(sizeof(int) * count);
	if (!doc_index)
		return (0);
	while (doc_idx < count)
	{
		while (ft_strcmp(head->str, "<<", 2) != 0 || head)
		{
			head = head->next;
			doc_idx++;
		}
		doc_index[k++] = doc_idx - 1;
	}
	return (doc_index);
}

void	insert_heredoc(int i, int doc_index, int doc_fd, char *limiter)// t_data data (data->doc_fd), i, *doc_index
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

int	check_heredoc(t_token *head)
{
	int	flag;

	flag = 0;
	while (head || ft_strcmp(head->str, "<<", 2) != 0) //type로 보아 파이프가 아니면 동작
	{
		if (cmp_heredoc(head))
		{
			flag = 1;
			break ;
		}
		head = (head->next);
	}
	if (flag == 1)
		return (1);
	else
		return (0);
}

char	*get_limiter(t_token *head, int doc_index)
{
	int		lim_index;
	char	*limiter;

	lim_index = doc_index + 1;
	while (lim_index--)
		head = head->next;
	limiter = ft_strdup(head->str);
	limiter = ft_strjoin(limiter, "\n");
	return (limiter);
}


void	run_heredoc(int count, t_token *head, t_data *data)
{
	int		i;
	char	*t;
	char	*limiter;
	int		*doc_index;
	int		k;

	k = 0;
	t = ".heredoc";
	i = 0;
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
		insert_heredoc(i, doc_index[i], data->doc_fd[i], limiter);
		i++;
	}
	closeall_fds();//열었던 쓰기전용 모든 fd 닫아주기
}
