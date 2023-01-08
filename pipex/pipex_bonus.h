/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 16:51:30 by gyopark           #+#    #+#             */
/*   Updated: 2023/01/08 14:23:29 by gyopark          ###   ########.fr       */
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
	int		infile;
	int		outfile;
	char	**path;
	int		pipe_size;	
	char	*cmd1;
	char	*cmd2;
	int		pipeA[2];
	int		pipeB[2];
}	t_struct;

int		odd_even_pipe_bonus(t_struct cmds, char **argv, char **envp, int i);
void	child_proc(t_struct cmds, int i, char **argv, char **envp);
void	parent_proc(t_struct cmds, int i, char **argv, char **envp);
int		parse_cmd(t_struct cmds, char **argv, char **envp);
char	**check_commands(char *argv);
char	*get_cmd(char **path, char *cmd);
void	first_parent_proc(t_struct cmds, char **argv, char **envp);
void	mid_parent_proc(t_struct cmds, int i, char **argv, char **envp);
void	last_parent_proc(t_struct cmds, int i, char **argv, char **envp);
void	first_child_proc(t_struct cmds, char **argv, char **envp);
void	mid_child_proc(t_struct cmds, int i, char **argv, char **envp);
void	last_child_proc(t_struct cmds, int i,char **argv, char **envp);
void	exit_err(const char *str);

#endif
