/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doc_open1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 16:28:36 by gyopark           #+#    #+#             */
/*   Updated: 2023/02/11 13:00:52 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	heredoc_file_make(int fd, char *limiter)
{
	char	*feed_line;
	char	*line;
	int		signo;

	signo = 0;
	while (1)
	{
		line = readline("here_doc> ");
		if (!line || ft_strncmp(line, limiter, ft_strlen(line)) == 0)
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

int	open_file(char *filename, int idx, t_doc **doc)
{
	int		fd;

	fd = open(filename, O_WRONLY | O_CREAT, 0644);
	if (fd == -1)
	{
		filename = ft_strjoin(filename, ": ");
		exit_error(filename, 0, 1);
		free(filename);
	}
	(*doc)->name[idx] = ft_strdup(filename);
	return (fd);
}

void	make_doc_files(int count, t_doc *doc)
{
	int		idx;
	char	*filename;
	int		fd;

	filename = "/tmp/.here_doc";
	idx = 0;
	while (idx < count)
	{
		if (access(filename, F_OK) == -1)
			fd = open_file(filename, idx, &doc);
		else
		{
			filename = ft_strjoin(filename, "1");
			continue ;
		}
		printf("i : %d, limiter : %s\n\n", idx, doc->limiters[idx]);
		heredoc_file_make(fd, doc->limiters[idx]);
		idx++;
		close(fd);
	}
}

int	count_heredoc(char *line)
{
	const int	len = ft_strlen(line);
	int			cnt;
	int			i;

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
	// doc_str = ft_split(line, ' ');
	doc_str = myfunc_split(line, 0, 0, 0);
	printf("\n\ndoc_str : %s, %s\n\n", doc_str[0], doc_str[1]);
	doc->count = get_doc_count(doc_str);
	if (doc->count == -1)
		return (-1);
	doc->name = (char **)malloc(sizeof(char *) * doc->count);
	doc->limiters = (char **)malloc(sizeof(char *) * doc->count);
	doc->limiters = get_limiter(doc_str, doc);
	make_doc_files(doc->count, doc);
	return (0);
}
