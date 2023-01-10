/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 16:51:30 by gyopark           #+#    #+#             */
/*   Updated: 2023/01/10 21:12:51 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>
# include <stdio.h>
# include <errno.h>
# include "libft/libft.h"

# define EXIT_FAILURE 1

typedef struct s_struct
{
	int		argc;
	int		ifd;
	int		hfd;
	char	**path;
	int		pipe_size;
	int		fd[2];
}	t_struct;

int		parse_cmd(t_struct cmds, char **argv, char **envp);
char	**check_commands(char *argv);
char	*get_cmd(char **path, char *cmd);
int		ft_perror(char *str, int exit_code);
void	ft_strerror(void);
void	first_child_proc(t_struct cmds, char **argv, char **envp, int *i);
void	child_proc(t_struct cmds, char *arg, char **envp);
void	parent_proc(t_struct cmds);
void	execute(t_struct cmds, char *arg, char **envp);

int		is_heredoc(char *arg);
int		here_doc(t_struct cmds, char *limiter);
int		go_heredoc(t_struct cmds, char **argv);
void	cmd_error_handle(char *exec_cmd);
void	error_handle(char *message, char **argv);
void	command_not_found(char *cmd);

#endif
