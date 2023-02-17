/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark < gyopark@student.42seoul.kr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 16:43:30 by gyopark           #+#    #+#             */
/*   Updated: 2023/02/17 19:37:12 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_check(char *str)
{
	if (!ft_strncmp("echo", str, 4) && str[4] == 0)
		return (1);
	if (!ft_strncmp("cd", str, 2) && str[2] == 2)
		return (1);
	if (!ft_strncmp("pwd", str, 4) && str[3] == 0)
		return (1);
	if (!ft_strncmp("export", str, 7) && str[6] == 0)
		return (1);
	if (!ft_strncmp("unset", str, 6) && str[5] == 0)
		return (1);
	if (!ft_strncmp("env", str, 4) && str[3] == 0)
		return (1);
	if (!ft_strncmp("exit", str, 5) && str[4] == 0)
		return (1);
	return (0);
}

int	built_pwd(void)
{
	char	t[2048];

	getcwd(t, 2048);
	printf("%s\n", t);
	g_exit_code = 0;
	return (1);
}

int	built_unset(char **builtin, t_list *head)
{
	int	i;

	i = 1;
	if (!builtin[1])
	{
		g_exit_code = 0;
		return (1);
	}
	while ((builtin)[i])
	{
		if (builtin[i])
			del_one(builtin[i], head);
		i++;
	}
	g_exit_code = 0;
	return (1);
}

int	check_builtin_2(char **builtin, t_list *head)
{
	int	result;

	result = -1;
	if (!ft_strncmp(builtin[0], "unset", 6) || (ft_strnstr(builtin[0], "unset",
				ft_strlen(builtin[0])) && access(builtin[0], X_OK) != -1))
		result = built_unset(builtin, head);
	else if (!ft_strncmp(builtin[0], "env", 4) || (ft_strnstr(builtin[0], "env",
				ft_strlen(builtin[0])) && access(builtin[0], X_OK) != -1))
		result = built_env(builtin, head);
	else if (!ft_strncmp(builtin[0], "exit", 5) || (ft_strnstr(builtin[0],
				"exit", ft_strlen(builtin[0])) && access(builtin[0],
				X_OK) != -1))
		result = call_exit(builtin);
	return (result);
}

int	check_builtin(char **builtin, t_list *head, char **envp)
{
	int	result;

	result = -1;
	if (!ft_strncmp(builtin[0], "echo", 5) || (ft_strnstr(builtin[0], "echo",
				ft_strlen(builtin[0])) && access(builtin[0], X_OK) != -1))
		result = built_echo(builtin);
	else if (!ft_strncmp(builtin[0], "cd", 3) || (ft_strnstr(builtin[0], "cd",
				ft_strlen(builtin[0])) && access(builtin[0], X_OK) != -1))
		result = built_cd(builtin, envp);
	else if (!ft_strncmp(builtin[0], "pwd", 4) || (ft_strnstr(builtin[0], "pwd",
				ft_strlen(builtin[0])) && access(builtin[0], X_OK) != -1))
		result = built_pwd();
	else if (!ft_strncmp(builtin[0], "export", 7) || (ft_strnstr(builtin[0],
				"export", ft_strlen(builtin[0])) && access(builtin[0],
				X_OK) != -1))
		result = built_export(builtin, head);
	else
		result = check_builtin_2(builtin, head);
	return (result);
}
