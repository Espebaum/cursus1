/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 21:24:06 by gyopark           #+#    #+#             */
/*   Updated: 2023/01/04 23:00:20 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exit_err(const char *str)
{
	write(1, str, ft_strlen(str));
	exit(0);
}

char	*get_cmd(char **path, char *cmd)
{
	int		i;
	int		fd;
	char	*path_cmd;
	char	*tmp;

	path_cmd = ft_strjoin("/", cmd);
	fd = 0;
	i = 0;
	while (path[i])
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
		i++;
	}
	free(path_cmd);
	return (NULL);
}

char	**check_commands(char *argv)
{
	char	**cmd;

	cmd = ft_split(argv, ' ');
	if (cmd == NULL)
		exit_err("missing command!");
	return (cmd);
}

char	**get_path(char **envp)
{
	while (*envp && ft_strncmp(*envp, "PATH", 4))
		envp++;
	return (ft_split(*envp + 5, ':'));
}

int	main(int argc, char **argv, char **envp)
{
	t_struct	cmds;

	if (argc == 5)
	{
		cmds.infile = open(argv[1], O_RDONLY);
		cmds.outfile = open(argv[argc - 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
		if (cmds.infile == -1 || cmds.outfile == -1)
			exit_err("file error!");
		cmds.path = get_path(envp);
		cmds.size = argc - 4;
		parse_cmd(cmds, argv, envp);
	}
	else
		exit_err("argument error!");
}
