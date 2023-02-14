/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_env1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark < gyopark@student.42seoul.kr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 16:25:16 by gyopark           #+#    #+#             */
/*   Updated: 2023/02/14 22:07:11 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_env_num(char *envp)
{
	int		cnt;
	char	*temp;

	temp = envp;
	cnt = 0;
	if (temp[0] != '\0')
	{
		while (*temp != '=')
		{
			cnt++;
			temp++;
		}
	}
	return (cnt);
}

int	check_all_dollar(t_str **buf, char **str)
{
	int	i;

	i = -1;
	if (**str == '\0')
	{
		push_str(*buf, '$');
		return (0);
	}
	while (**str == '$')
	{
		push_str(*buf, '$');
		(*str)++;
	}
	return (0);
}

int	env_read(t_str **buf, t_str **env, char *g_str)
{
	int	i;

	i = -1;
	if (ft_strlen((*env)->s) == 1 && (*env)->s[0] == '?')
	{
		while (g_str[++i])
			push_str(*buf, g_str[i]);
		free_str(*env);
		return (0);
	}
	return (1);
}

int	make_env_buf(t_str **buf, t_str **env, char **envp, char *meta_str)
{
	int		i;
	int		env_num;

	i = -1;
	while (envp[++i])
	{
		env_num = get_env_num(envp[i]);
		if (ft_strncmp((*env)->s, envp[i], ft_max(ft_strlen((*env)->s),
					env_num)) == 0)
		{
			envp[i] += env_num + 1;
			while (*envp[i] != '\0')
			{
				push_str((*buf), *envp[i]);
				envp[i]++;
			}
			return (1);
		}
	}
	i = -1;
	if (meta_str)
		return (1);
	return (0);
}
