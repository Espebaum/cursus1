/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 16:03:57 by youngski          #+#    #+#             */
/*   Updated: 2023/01/31 17:37:34 by gyopark          ###   ########.fr       */
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

int check_command(char **path, char *cmd)
{
	int		i;
	int		fd;
	char	*path_cmd;
	char	*tmp;

	if (access(cmd, X_OK) != -1)
		return (0);
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
			return (0);
		}
		close(fd);
		free(tmp);
	}
	free(path_cmd);
	return (1);
}
