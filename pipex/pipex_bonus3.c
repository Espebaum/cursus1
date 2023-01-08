/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 13:59:40 by gyopark           #+#    #+#             */
/*   Updated: 2023/01/08 19:38:41 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	execute_bonus(t_struct cmds, char *arg, char **envp)
{
	char	**arg_cmd;
	char	*exec_cmd;

	arg_cmd = check_commands_bonus(arg);
	exec_cmd = get_cmd_bonus(cmds.path, arg_cmd[0]);
	if (execve(exec_cmd, arg_cmd, envp) == -1)
		exit_err_bonus("execute error");
}
