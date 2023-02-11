/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doc_open1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark < gyopark@student.42seoul.kr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 16:28:36 by gyopark           #+#    #+#             */
/*   Updated: 2023/02/11 18:52:28 by gyopark          ###   ########.fr       */
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

void	make_doc_files(int count, t_doc *doc)
{
	int		idx;
	char	*filename;
	int		fd;
	int		pid;
	int		pipe_fd[2];
	char	**temp;
	char	*str;
	int		asdf;

	filename = "/tmp/.here_doc";
	idx = 0;
	pipe(pipe_fd);
	pid = fork();
	if (pid == 0)
	{
		while (idx < count)
		{
			if (access(filename, F_OK) == -1)
				fd = open_file(filename, idx, &doc, pipe_fd);
			else
			{
				filename = ft_strjoin(filename, "1");
				continue ;
			}
			//printf("i : %d, limiter : %s\n\n", idx, doc->limiters[idx]);
			heredoc_file_make(fd, doc->limiters[idx], pipe_fd);
			idx++;
			close(fd);
		}
		close(pipe_fd[1]);
		close(pipe_fd[0]);
		exit(0); //종료 처리할것
	}
	else
	{
		close(pipe_fd[1]);
		waitpid(pid, NULL, 0);
		while (idx <= doc->count)
		{
			str = get_next_line(pipe_fd[0]);
			if (!str)
				break ;
			asdf = ft_strlen(str);
			str[asdf - 1] = 0;
			printf("s : %s\n", str);
			doc->name[idx++] = str;
		}
		close(pipe_fd[0]);
	}
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
	// doc_str = ft_split(line, ' ');
	doc_str = myfunc_split(line, 0, 0, 0);
	printf("\n\ndoc_str : %s, %s\n\n", doc_str[0], doc_str[1]);
	doc->count = get_doc_count(doc_str);
	if (doc->count == -1)
		return (-1);
	doc->name = (char **)malloc(sizeof(char *) * doc->count);
	doc->limiters = (char **)malloc(sizeof(char *) * doc->count);
	doc->limiters = get_limiter(doc_str, doc);
	if (doc->count > 0)
		make_doc_files(doc->count, doc);
	return (0);
}
