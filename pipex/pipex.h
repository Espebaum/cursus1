/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 16:51:30 by gyopark           #+#    #+#             */
/*   Updated: 2023/01/14 14:02:14 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include "libft/libft.h"

# define INFILE 0
# define OUTFILE 1 
# define EINVAL 22

typedef struct s_struct
{
	int		ifd;
	int		argc;
	char	**path;
	int		fd[2];
}	t_struct;

int		open_file(t_struct cmds, char **argv, char *filename, int mode);
int		open_pipe(t_struct cmds, char **argv, char **envp);
char	**check_commands(char *argv);
char	*get_cmd(char **path, char *cmd);

void	ft_strerror(int errno);
int		ft_perror(char *str, int exit_code);
int		wait_all(pid_t last_pid);

#endif
