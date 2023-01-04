/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 16:51:30 by gyopark           #+#    #+#             */
/*   Updated: 2023/01/04 23:01:03 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>
# include <stdio.h>
# include "libft/libft.h"

typedef struct s_struct
{
	int		infile;
	int		outfile;
	char	*cmd1;
	char	*cmd2;
	char	**path;
	int		size;
	int		fd[2];
}	t_struct;

void	parse_cmd(t_struct cmds, char **argv, char **envp);
char	**check_commands(char *argv);
char	*get_cmd(char **path, char *cmd);
void	open_pipe(t_struct cmds, char **arg_cmd1, char **arg_cmd2, char **envp);
void	exit_err(const char *str);

#endif
