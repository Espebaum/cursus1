/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_line5.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 19:58:12 by gyopark           #+#    #+#             */
/*   Updated: 2023/02/09 20:07:21 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**keep_execve_par(t_token **head, char **builtin, int *cmd_flag)
{
	char	**ret;
	char	*cmd;

	cmd = (*head)->str;
	ret = copy_orders(builtin);
	ret = add_order(ret, cmd, cmd_flag[0]);
	(*head) = (*head)->next;
	cmd_flag[0] = 1;
	return (ret);
}

char	**keep_execve_chd(t_data data, t_token **head, char **t, int *cmd_flag)
{
	char		**ret;
	char		*cmd;
	struct stat	file_info;

	cmd = (*head)->str;
	lstat(cmd, &file_info);
	if (cmd != NULL && cmd[0] != '\0')
	{
		if (cmd_flag[0] == '\0')
			if (builtin_check(cmd) == 0)
				if (check_command(data.path, cmd) == 0
					|| S_ISDIR(file_info.st_mode))
					exit_error(cmd, 0, 127);
	}
	else
		exit_error(cmd, 0, 127);
	ret = copy_orders(t);
	ret = add_order(ret, cmd, cmd_flag[0]);
	(*head) = (*head)->next;
	cmd_flag[0] = 1;
	return (ret);
}

int	with_signal_exit(int *signo, int *status, int *i)
{
	*signo = WTERMSIG(*status);
	if (*signo == SIGINT && (*i)++ == 0)
		printf("\n");
	if (*signo == SIGQUIT && (*i)++ == 0)
		printf("Quit: 3\n");
	g_exit_code = 128 + *signo;
	return (g_exit_code);
}

int	wait_all(pid_t last_pid)
{
	pid_t	pid;
	int		signo;
	int		status;
	int		i;

	i = 0;
	pid = 1;
	while (pid != -1)
	{
		pid = wait(&status);
		if (pid == last_pid)
		{
			if (WIFSIGNALED(status))
				g_exit_code = with_signal_exit(&signo, &status, &i);
			else
				g_exit_code = WEXITSTATUS(status);
		}
	}
	return (g_exit_code);
}
