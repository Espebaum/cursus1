/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 13:59:40 by gyopark           #+#    #+#             */
/*   Updated: 2023/01/08 14:23:40 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	first_child_proc(t_struct cmds, char **argv, char **envp)
{
	char	**arg_cmd1;

	arg_cmd1 = check_commands(argv[2]);
	close(cmds.pipeA[0]);
	dup2(cmds.infile, STDIN_FILENO);
	dup2(cmds.pipeA[1], STDOUT_FILENO);
	close(cmds.infile);
	close(cmds.pipeA[1]);
	if (execve(cmds.cmd1, arg_cmd1, envp) == -1)
		exit_err("execute error!");
}

void	first_parent_proc(t_struct cmds, char **argv, char **envp);
{

}
