/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 14:12:35 by gyopark           #+#    #+#             */
/*   Updated: 2023/02/03 13:31:45 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	wait_all(pid_t last_pid)
{
	pid_t	pid;
	int		temp;
	int		status;

	pid = 1;
	while (pid != -1)
	{
		pid = wait(&temp);
		if (pid == last_pid)
			status = temp;
	}
	return (WEXITSTATUS(status));
}

t_token	*get_next_tmp(t_token *temp)
{
	while (temp && temp->type != T_PIPE)
		temp = temp->next;
	if (temp)
		temp = temp->next;
	return (temp);
}

char	*get_cmd(char **path, char *cmd)
{
	int		i;
	int		fd;
	char	*path_cmd;
	char	*tmp;

	if (access(cmd, X_OK) != -1)
		return (cmd);
	if (!path)
		return (NULL); //ft_perror("missing path", 1);
	path_cmd = ft_strjoin("/", cmd);
	i = -1;
	while (path[++i])
	{
		tmp = ft_strjoin(path[i], path_cmd);
		fd = access(tmp, X_OK);
		if (fd != -1)
		{
			free(path_cmd);
			return (tmp);
		}
		close(fd);
		free(tmp);
	}
	free(path_cmd);
	return (NULL);
}

char	**get_path(char **envp)
{
	while (*envp && ft_strncmp(*envp, "PATH", 4))
		envp++;
	if (!*envp)
		return (0);
	return (ft_split(*envp + 5, ':'));
}