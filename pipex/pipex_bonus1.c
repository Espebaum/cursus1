/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 21:24:06 by gyopark           #+#    #+#             */
/*   Updated: 2023/01/10 21:12:35 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	**get_path(char **envp)
{
	while (*envp && ft_strncmp(*envp, "PATH", 4))
		envp++;
	return (ft_split(*envp + 5, ':'));
}

char	**check_commands(char *argv)
{
	char	**cmd;

	cmd = ft_split(argv, ' ');
	if (cmd == NULL)
		ft_perror("missing command!", EXIT_FAILURE);
	return (cmd);
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

int	main(int argc, char **argv, char **envp)
{
	t_struct	cmds;
	int			result;

	result = 0;
	if (argc >= 5)
	{
		cmds.path = get_path(envp);
		cmds.argc = argc;
		cmds.pipe_size = argc - 4;
		if (is_heredoc(argv[1]))
			cmds.hfd = go_heredoc(cmds, argv);
		else
			cmds.ifd = open(argv[1], O_RDONLY);
		if (cmds.ifd == -1)
			error_handle("infile error", argv);
		result = parse_cmd(cmds, argv, envp);
	}
	else
		ft_perror("argument error!", EXIT_FAILURE);
	return (result);
}
