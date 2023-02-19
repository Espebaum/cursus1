/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark < gyopark@student.42seoul.kr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 20:28:23 by gyopark           #+#    #+#             */
/*   Updated: 2023/02/19 17:49:06 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_home(char **envp)
{
	while (*envp && ft_strncmp(*envp, "HOME", 4))
		envp++;
	if (!*envp)
		return (0);
	return (*envp + 5);
}

int	move_home(char *home)
{
	if (!home)
	{
		printf("cd: HOME not set\n");
		g_exit_code = 1;
		return (1);
	}
	else
	{
		if (chdir(home) != 0)
		{
			printf("cd: %s: No such file or directory\n", home);
			g_exit_code = 1;
			return (1);
		}
	}
	return (0);
}

int	built_cd(char **t, char **envp)
{
	char	**temp;
	char	*home;

	temp = deep_copy_env(envp);
	home = get_home(temp);
	if (t[1] == 0)
	{
		if (move_home(home) == 1)
		{
			free_spl(temp);
			return (1);
		}
	}
	else
	{
		if (chdir(t[1]) != 0)
		{
			printf("cd: %s: No such file or directory\n", t[1]);
			g_exit_code = 1;
			return (1);
		}
	}
	g_exit_code = 0;
	free_spl(temp);
	return (1);
}
