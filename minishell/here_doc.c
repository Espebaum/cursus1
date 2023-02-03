/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 16:28:36 by gyopark           #+#    #+#             */
/*   Updated: 2023/02/03 20:58:08 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_doc	*init_doc(t_doc *doc)
{
	doc->name = NULL;
	doc->count = 0;
	doc->limiters = NULL;
	return (doc);
}

char	**get_limiter(char **doc_str, t_doc *doc)
{
	int		idx;
	char	**limiters;

	idx = 0;
	limiters = doc->limiters;
	while (doc_str[idx] && doc_str[idx + 1])
	{
		if (ft_strncmp(doc_str[idx], "<<", 3) == 0)
			limiters[idx] = doc_str[idx + 1];
		idx++;
	}
	return (limiters);
}

int	get_doc_count(char **doc_str)
{
	int		cnt;
	int		idx;

	idx = -1;
	cnt = 0;
	while (doc_str[++idx])
	{
		if (ft_strncmp(doc_str[idx], "<<", 3) == 0)
		{
			if (doc_str[idx + 1] && !ft_strncmp(doc_str[idx + 1], "<", 2))
				return (syntax_err());
			else if (doc_str[idx + 1] && !ft_strncmp(doc_str[idx + 1], ">", 2))
				return (syntax_err());
			else if (doc_str[idx + 1] && !ft_strncmp(doc_str[idx + 1], ">>", 3))
				return (syntax_err());
			else if (doc_str[idx + 1] && !ft_strncmp(doc_str[idx + 1], "<<", 3))
				return (syntax_err());
			else if (doc_str[idx + 1] && !ft_strncmp(doc_str[idx + 1], "|", 2))
				return (syntax_err());
			else if (!doc_str[idx + 1])
				return (syntax_err());
			cnt++;
		}
	}
	return (cnt);
}

void	heredoc_file_make(int fd, char *limiter)
{
	char	*line;

	while (1)
	{
		write(1, "here_doc> ", 10);
		line = readline("");
		if (ft_strncmp(line, limiter, ft_strlen(line)) == 0 || !line)
		{
			free(line);
			break ;
		}
		line = ft_strjoin(line, "\n"); //안에 line free해줘야함 나중에
		write(fd, line, ft_strlen(line));
		free(line);
	}
}

void	make_doc_files(int count, t_doc *doc)
{
	int		i;
	char	*t;
	int		fd;

	t = "/tmp/.here_doc";
	i = 0;
	while (i < count)
	{
		if (access(t, F_OK) == -1)
		{
			fd = open(t, O_WRONLY | O_CREAT, 0777);
			doc->name[i] = ft_strdup(t);
		}
		else
		{
			t = ft_strjoin(t, "1");
			continue ;
		}
		heredoc_file_make(fd, doc->limiters[i]);
		i++;
		close(fd);
	}
}

int	open_heredoc(t_doc *doc, char *line)
{
	char	**doc_str;
	int		i;

	doc = init_doc(doc);
	i = -1;
	doc_str = ft_split(line, ' ');
	doc->count = get_doc_count(doc_str);
	if (doc->count == -1)
		return (-1);
	doc->name = (char **)malloc(sizeof(char *) * doc->count);
	doc->limiters = (char **)malloc(sizeof(char *) * doc->count);
	doc->limiters = get_limiter(doc_str, doc);
	make_doc_files(doc->count, doc);
	return (0);
}
