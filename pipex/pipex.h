/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 16:51:30 by gyopark           #+#    #+#             */
/*   Updated: 2023/01/11 20:37:43 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include "libft/libft.h"

# define INFILE 0
# define OUTFILE 1 

typedef struct s_struct
{
	int		ifd;
	int		ofd;
	int		argc;
	char	**path;
	int		pipe_size;
	int		fd[2];
}	t_struct;

int		open_file(t_struct cmds, char **argv, char *filename, int mode);
int		parse_cmd(t_struct cmds, char **argv, char **envp);
char	**check_commands(char *argv);
char	*get_cmd(char **path, char *cmd);
void	open_pipe(t_struct cmds, char **arg_cmd1, char **arg_cmd2, char **envp);
void	exit_err(const char *str);
int		ft_strcmp(const char *s1, const char *s2);

void	cmd_error_handle(char *exec_cmd);
void	error_handle(char *message, char **argv);
void	command_not_found(char *cmd);
void	ft_strerror(char *str, int exit_code);
int		wait_all(pid_t last_pid);
int		ft_perror(char *str, int exit_code);

#endif
