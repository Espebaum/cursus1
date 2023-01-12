/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 16:51:30 by gyopark           #+#    #+#             */
/*   Updated: 2023/01/12 20:18:01 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include "gnl/get_next_line.h"
# include "libft/libft.h"

# define INFILE 0
# define OUTFILE 1 

typedef struct s_struct
{
	int		argc;
	int		ifd;
	int		hfd;
	char	**path;
	int		pipe_size;
	int		fd[2];
}	t_struct;

typedef enum e_err {
	ENOENT = 2,
	EIO = 5,
	EACCES = 13,
	EISDIR = 21,
	EINVAL = 22
}	t_err;

int		open_file(t_struct cmds, char **argv, char *filename, int mode);
int		open_pipe(t_struct cmds, char **argv, char **envp);
char	**check_commands(char *argv);
char	*get_cmd(char **path, char *cmd);
int		ft_perror(char *str, int exit_code);
void	first_child_proc(t_struct cmds, char **argv, char **envp, int *i);
void	child_proc(t_struct cmds, char *arg, char **envp);
void	parent_proc(t_struct cmds);
void	execute(t_struct cmds, char *arg, char **envp);

int		is_heredoc(char *arg);
int		here_doc(t_struct cmds, char *limiter);
int		go_heredoc(t_struct cmds, char **argv);
void	cmd_error_handle(char *exec_cmd);
void	file_error_handle(t_struct cmds, char **argv, int fileno);
int		wait_all(pid_t last_pid);
void	ft_strerror(int errno);

#endif
