/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 16:03:57 by youngski          #+#    #+#             */
/*   Updated: 2023/02/08 21:32:39 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**get_path(char **envp)
{
	while (*envp && ft_strncmp(*envp, "PATH", 4))
		envp++;
	if (!*envp)
		return (0);
	return (ft_split(*envp + 5, ':'));
}

int	check_command(char **path, char *cmd)
{
	int			i;
	int			fd;
	char		*path_cmd;
	char		*tmp;
	struct stat	file_info;

	if (ft_strncmp(cmd, "./", 2) == 0 || ft_strncmp(cmd, "/", 1) == 0)
	{
		if (lstat(cmd, &file_info) < 0)
			exit_error(cmd, 0, 1);
		else if (S_ISDIR(file_info.st_mode))
		{
			ft_putstr_fd(cmd, 2);
			write(2, ": ", 2);
			ft_putstr_fd("is a directory\n", 2);
			exit (126);
		}
	}
	if (access(cmd, X_OK) != -1)
		return (1);
	if (!path)
		exit_error("missing path!", 0, 1);
	path_cmd = ft_strjoin("/", cmd);
	i = -1;
	while (path[++i])
	{
		tmp = ft_strjoin(path[i], path_cmd);
		fd = access(tmp, X_OK);
		if (fd != -1)
		{
			free(path_cmd);
			return (1);
		}
		close(fd);
		free(tmp);
	}
	free(path_cmd);
	return (0);
}
