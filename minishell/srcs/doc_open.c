/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doc_open.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 16:28:36 by gyopark           #+#    #+#             */
/*   Updated: 2023/02/07 21:56:43 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_doc	*init_doc(t_doc *doc)
{
	doc->name = NULL;
	doc->count = 0;
	doc->limiters = NULL;
	doc->zero = 0;
	return (doc);
}

char	*get_rid_str(int left, int right, char *doc_str)
{
	const int	len = ft_strlen(doc_str);
	char		*limiter;
	int			str_idx;
	int			lim_idx;

	str_idx = -1;
	lim_idx = 0;
	limiter = (char *) malloc(sizeof(char) * (len - 1));
	limiter[len - 2] = '\0';
	while (++str_idx < len)
	{
		if (str_idx == left || str_idx == right)
		{
			str_idx++;
			if (str_idx == right)
				str_idx++;
		}
		limiter[lim_idx++] = doc_str[str_idx];
	}
	return (limiter);
}

char	*rid_quotes(char *doc_str)
{
	char		*limiter;
	int			i;
	int			left;
	int			right;

	i = -1;
	left = 0;
	right = 0;
	while (doc_str[++i])
	{
		if ((doc_str[0] == '\"' && doc_str[1] == '\"')
			|| (doc_str[0] == '\'' && doc_str[1] == '\''))
		{
			left = 0;
			right = 1;
			break ;
		}
		if (doc_str[i] == '\"' || doc_str[i] == '\'')
		{
			if (left == 0)
				left = i;
			else
				right = i;
		}
	}
	if ((left == 0 && right == 1) || left != 0)
		limiter = get_rid_str(left, right, doc_str);
	else
		return (doc_str);
	return (limiter);
}

char	**get_limiter(char **doc_str, t_doc *doc)
{
	int		idx;
	int		j;
	char	**limiters;

	idx = 0;
	limiters = doc->limiters;
	j = 0;
	while (doc_str[idx] && doc_str[idx + 1])
	{
		if (ft_strncmp(doc_str[idx], "<<", 3) == 0)
			limiters[j++] = rid_quotes(doc_str[idx + 1]);
		idx++;
	}
	return (limiters);
}

int	get_doc_count(char **doc_str)
{
	int		cnt;
	int		idx;

	if (doc_str[0][0] == '\0')
		return (1);
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
		line = readline("here_doc> ");
		if (!line || ft_strncmp(line, limiter, ft_strlen(line)) == 0)
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
	int		idx;
	char	*filename;
	int		fd;

	filename = "/tmp/.here_doc";
	idx = 0;
	while (idx < count)
	{
		if (access(filename, F_OK) == -1)
		{
			fd = open(filename, O_WRONLY | O_CREAT, 0644);
			if (fd == -1)
			{
				filename = ft_strjoin(filename, ": ");
				exit_error(filename, 0, 1);
				free(filename);
			}
			doc->name[idx] = ft_strdup(filename);
		}
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

int	open_heredoc(t_doc *doc, char *line)
{
	char	**doc_str;

	doc = init_doc(doc);
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
//리미터 쿼트 안에 있으면 쿼트 제거
