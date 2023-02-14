/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doc_open1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark < gyopark@student.42seoul.kr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 16:28:36 by gyopark           #+#    #+#             */
/*   Updated: 2023/02/14 19:02:49 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	heredoc_file_make(int fd, char *limiter, int *pipe_fd)
{
	char	*feed_line;
	char	*line;
	int		signo;

	signo = 0;
	while (1)
	{
		line = readline("here_doc> ");
		if ((ft_strncmp(line, limiter, ft_strlen(limiter) + 1) == 0)
			&& line[0] != 0 || !line)
		{
			free(line);
			break ;
		}
		feed_line = ft_strjoin(line, "\n");
		free(line);
		write(fd, feed_line, ft_strlen(feed_line));
		free(feed_line);
	}
}

int	open_file(char *filename, int idx, t_doc **doc, int *pipe_fd)
{
	int		fd;
	char	*t;

	fd = open(filename, O_WRONLY | O_CREAT, 0644);
	if (fd == -1)
	{
		filename = ft_strjoin(filename, ": \n");
		exit_error(filename, 0, 1);
		free(filename);
	}
	else
		filename = ft_strjoin(filename, "\n");
	t = ft_strdup(filename);
	(*doc)->name[idx] = t;
	write(pipe_fd[1], t, ft_strlen(t));
	return (fd);
}

int	count_heredoc(char *line)
{
	int	len;
	int	cnt;
	int	i;

	len = ft_strlen(line);
	i = -1;
	cnt = 0;
	while (++i < len - 1)
	{
		if (line[i] == '<' && line[i + 1] == '<')
		{
			cnt++;
			i++;
		}
	}
	return (cnt);
}

int	open_heredoc(t_doc *doc, char *line)
{
	char	**doc_str;

	doc = init_doc(doc);
	doc_str = myfunc_split(line, 0, 0, 0);
	printf("doc_str[0] : %s doc_str[1] : %s\n", doc_str[0], doc_str[1]);
	doc->count = get_doc_count(doc_str);
	if (doc->count == -1)
		return (-1);
	doc->name = (char **)malloc(sizeof(char *) * doc->count);
	doc->limiters = (char **)malloc(sizeof(char *) * doc->count);
	doc->limiters = get_limiter(doc_str, doc);
	if (doc->count > 0)
		make_doc_files(doc->count, doc);
	if (g_exit_code == 0)
		return (1);
	else if (g_exit_code == 15)
	{
		g_exit_code = 0;
		return (3);
	}
	else
		return (2);
}
