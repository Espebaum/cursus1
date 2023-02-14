/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doc_open3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark < gyopark@student.42seoul.kr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 18:19:56 by gyopark           #+#    #+#             */
/*   Updated: 2023/02/14 21:38:39 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	doc_child(int idx, int count, t_doc **doc, int *pipe_fd)
{
	int		fd;
	char	*filename;

	filename = "/tmp/.here_doc";
	set_signal(DOC, SHE);
	while (idx < count)
	{
		if (access(filename, F_OK) == -1)
			fd = open_file(filename, idx, doc, pipe_fd);
		else
		{
			filename = ft_strjoin(filename, "1");
			continue ;
		}
		printf("limiter : %s\n", (*doc)->limiters[idx]);
		heredoc_file_make(fd, (*doc)->limiters[idx], pipe_fd);
		idx++;
		close(fd);
	}
	close(pipe_fd[1]);
	close(pipe_fd[0]);
	if (g_exit_code == 15)
		exit (g_exit_code);
	g_exit_code = 0;
	exit(g_exit_code);
}
//31 printf("i : %d, limiter : %s\n\n", idx, doc->limiters[idx]);

void	doc_parent(int idx, int count, t_doc **doc, int *pipe_fd)
{
	char	*str;
	int		len;

	len = 0;
	while (idx <= (*doc)->count)
	{
		str = get_next_line(pipe_fd[0]);
		if (!str)
			break ;
		len = ft_strlen(str);
		str[len - 1] = 0;
		(*doc)->name[idx++] = str;
	}
}

void	make_doc_files(int count, t_doc *doc)
{
	int		pid;
	int		pipe_fd[2];
	int		status;
	char	**temp;
	int		asdf;

	pipe(pipe_fd);
	pid = fork();
	set_signal(IGN, IGN);
	if (pid == 0)
		doc_child(0, count, &doc, pipe_fd);
	else
	{
		close(pipe_fd[1]);
		waitpid(pid, &status, 0);
		g_exit_code = WEXITSTATUS(status);
		doc_parent(0, count, &doc, pipe_fd);
		close(pipe_fd[0]);
	}
}
// printf("exit_code : %d\n", g_exit_code);
