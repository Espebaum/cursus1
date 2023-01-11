/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 21:24:06 by gyopark           #+#    #+#             */
/*   Updated: 2023/01/11 22:21:49 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	open_file(t_struct cmds, char **argv, char *filename, int mode)
{
	if (mode == INFILE)
	{
		if (access(filename, F_OK))
		{
			write(2, "pipex: ", 7);
			write(2, filename, ft_strlen(filename));
			write(2, ": No such file or directory\n", 28);
			return (0);
		}
		return (open(filename, O_RDONLY));
	}
	else
		return (open(argv[cmds.argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644));
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
	int			result;

	result = 0;
	if (argc == 5)
	{
		cmds.argc = argc;
		cmds.ifd = open_file(cmds, argv, argv[1], INFILE);
		if (cmds.ifd == -1)
			ft_perror("infile error!", EXIT_FAILURE);
		cmds.path = get_path(envp);
		cmds.pipe_size = argc - 4;
		result = parse_cmd(cmds, argv, envp);
	}
	else
		ft_perror("Invalid number of arguments", EXIT_FAILURE);
	return (result);
}
