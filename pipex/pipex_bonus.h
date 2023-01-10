/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 16:51:30 by gyopark           #+#    #+#             */
/*   Updated: 2023/01/10 14:15:00 by gyopark          ###   ########.fr       */
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

typedef struct s_struct
{
	int		argc;
	int		ifd;
	int		hfd;
	char	**path;
	int		pipe_size;
	int		fd[2];
}	t_struct;

int		parse_cmd_bonus(t_struct cmds, char **argv, char **envp);
char	**check_commands_bonus(char *argv);
char	*get_cmd_bonus(char **path, char *cmd);
void	exit_err_bonus(const char *str);
void	first_child_proc_bonus(t_struct cmds, char **argv, char **envp);
void	child_proc_bonus(t_struct cmds, char *arg, char **envp);
void	parent_proc_bonus(t_struct cmds);
void	execute_bonus(t_struct cmds, char *arg, char **envp);

int		is_heredoc(char *arg);
int		here_doc(t_struct cmds, char *limiter);
int		go_heredoc(t_struct cmds, char **argv);

#endif
