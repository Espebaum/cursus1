/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 16:03:57 by youngski          #+#    #+#             */
/*   Updated: 2023/02/03 20:12:11 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../minishell.h"

// void	close_all_opend_heredoc_fd(t_data *data, int count)
// {
// 	int	i;

// 	i = -1;
// 	while (++i < count)
// 		close(data->doc_fd[i]);
// }

// int	check_heredoc(t_token *head)
// {
// 	int	flag;

// 	flag = 0;
// 	while (head || ft_strncmp(head->str, "<<", 2) != 0)
// 	{
// 		head = (head->next);
// 		if (!ft_strncmp(head->str, "<<", 2) || !ft_strncmp(head->str, "|", 1))
// 		{
// 			flag = !(ft_strncmp(head->str, "<<", 2));
// 			break ;
// 		}
// 	}
// 	if (flag == 1)
// 		return (1);
// 	else
// 		return (0);
// }

// void	heredoc_file_make(int doc_index, int doc_fd, char *limiter)
// {
// 	char	*line;

// 	(void) doc_index; // doc_index 사용 안함
// 	while (1)
// 	{
// 		write(1, "here_doc> ", 10);
// 		line = readline("");
// 		if (ft_strncmp(line, limiter, ft_strlen(line)) == 0 || !line)
// 		{
// 			free(line);
// 			break ;
// 		}
// 		write(doc_fd, line, ft_strlen(line));
// 		free(line);
// 	}
// }

// char	*get_limiter(t_token *head, int doc_index)
// {
// 	char	*limiter;
// 	char	*limiter_eol;

// 	head = head->next;
// 	while (doc_index--)
// 		head = head->next;
// 	limiter = ft_strdup(head->str);
// 	limiter_eol = ft_strjoin(limiter, "\n");
// 	free(limiter);
// 	return (limiter_eol);
// }

// int	*find_heredoc_index(t_token *head, int count)
// {
// 	int		*doc_index;
// 	int		doc_idx;
// 	int		k;

// 	k = 0;
// 	doc_idx = 0;
// 	doc_index = (int *)malloc(sizeof(int) * count);
// 	if (!doc_index)
// 		return (0);
// 	while (head)
// 	{
// 		if (ft_strncmp(head->str, "<<", 2) != 0 && head)
// 			doc_idx++;
// 		else
// 			doc_index[k++] = doc_idx++;
// 		head = head->next;
// 	}
// 	return (doc_index);
// }
// //&& doc_idx < token_len