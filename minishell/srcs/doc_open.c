/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doc_open.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 16:28:36 by gyopark           #+#    #+#             */
/*   Updated: 2023/02/08 23:01:58 by gyopark          ###   ########.fr       */
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

int	have_quotes(char *doc_str)
{
	const int	len = ft_strlen(doc_str);
	int			i;

	i = -1;
	while (++i < len)
		if (doc_str[i] == '\'' || doc_str[i] == '\"')
			return (1);
	return (0);
}

char	*get_rid_str(char *doc_str, char *limiter)
{
	int		i;
	int		lim_idx;

	i = -1;
	lim_idx = 0;
	while (doc_str[++i])
	{
		if (doc_str[i] == '\'')
			while (doc_str[++i] != '\'')
				limiter[lim_idx++] = doc_str[i];
		else if (doc_str[i] == '\"')
			while (doc_str[++i] != '\"')
				limiter[lim_idx++] = doc_str[i];
		else
			limiter[lim_idx++] = doc_str[i];
	}
	return (limiter);
}

char	*rid_quotes(char *doc_str)
{
	int		i;
	char	*limiter;
	int		limiter_len;

	i = -1;
	limiter_len = 0;
	while (doc_str[++i])
	{
		if (doc_str[i] == '\'')
			while (doc_str[++i] != '\'')
				limiter_len++;
		else if (doc_str[i] == '\"')
		{
			while (doc_str[++i] != '\"')
				limiter_len++;
		}
		else
			limiter_len++;
	}
	limiter = (char *) malloc(sizeof(char) * (limiter_len + 1));
	limiter[limiter_len] = '\0';
	limiter = get_rid_str(doc_str, limiter);
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

// char	**myfunc_split(char *line)
// {
// 	char	**ret;
// 	char	*line_temp;
// 	int		flag[3];
// 	int		i;
// 	int		j;
// 	int		count[2];

// 	i = 0;
// 	count[0] = count_heredoc(line);// make ret**
// 	count[1] = 0;// for spilted char * count
// 	flag[0] = 0;// for "  started
// 	flag[1] = 0;// for ' started
// 	flag[2] = 1;//middle while stop
// 	ret = (char **)malloc(sizeof(char *) * (count[0] + 1));	
// 	ret[count[0]] = 0;
// 	while (line_temp[i])
// 	{
// 		line_temp = ft_strnstr(line, "<<", ft_strlen(line));
// 		while (line_temp[i] && flag[2])
// 		{
// 			if (!line_temp)
// 				return 0;
// 			while (line_temp[i] == ' ')
// 				i++;
// 			if (line_temp == '\'' && flag[1] != 1)
// 			{
// 				flag[0] = 1;
// 				i++;
// 			}
// 			else if (line_temp == '\"' && flag[0] != 1)
// 			{
// 				flag[1] = 1;
// 				i++;
// 			}
// 			else if (flag[0] == 0 && flag[1] == 0 && line_temp == ' ')
// 				flag[2] = 0;
// 			else
// 			{
// 				count[2] += 1;
// 				i++;
// 			}
// 		}
// 		ret[j] = (char *)malloc(sizeof(char) * (count[2] + 1));
// 		ret[j][count[2]] = 0;
// 		j++;
// 	}
// 	while (line_temp[i])
// 	{
// 		line_temp = ft_strnstr(line, "<<", ft_strlen(line));
// 		j = 0;
// 		while (line_temp[i] && flag[3])
// 		{
// 			if (!line_temp)
// 				return 0;
// 			while (line_temp[i] == ' ')
// 				i++;
// 			if (line_temp == '\'' && flag[1] != 1)
// 			{
// 				flag[0] = 1;
// 				i++;
// 			}
// 			else if (line_temp == '\"' && flag[0] != 1)
// 			{
// 				flag[1] = 1;
// 				i++;
// 			}
// 			else if (flag[0] == 0 && flag[1] == 0 && line_temp == ' ')
// 				flag[2] = 0;
// 			else
// 			{
// 				count[2] += 1;
// 				ret[j][i] = line_temp[i];
// 				i++;
// 				j++;
// 			}
// 		}
// 	}
// }

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
