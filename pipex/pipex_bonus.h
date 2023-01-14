/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 16:51:30 by gyopark           #+#    #+#             */
/*   Updated: 2023/01/14 14:02:27 by gyopark          ###   ########.fr       */
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
# define EINVAL 22

typedef struct s_struct
{
	int		argc;
	int		ifd;
	int		hfd;
	char	**path;
	int		fd[2];
}	t_struct;

int		open_file(t_struct cmds, char **argv, char *filename, int mode);
int		open_pipe(t_struct cmds, char **argv, char **envp);
char	**check_commands(char *argv);
char	*get_cmd(char **path, char *cmd);
void	execute(t_struct cmds, char *arg, char **envp);

int		is_heredoc(char *arg);
int		go_heredoc(t_struct cmds, char **argv);
int		here_doc(t_struct cmds, char *limiter);
void	ft_strerror(int errno);
int		ft_perror(char *str, int exit_code);
int		wait_all(pid_t last_pid);

#endif
