/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 16:25:16 by gyopark           #+#    #+#             */
/*   Updated: 2023/02/09 22:08:43 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_env_num(char *envp)
{
	int		cnt;
	char	*temp;

	temp = envp;
	cnt = 0;
	while (*temp++ != '=')
		cnt++;
	if (cnt > 1)
		cnt--;
	return (cnt);
}

int	check_all_dollar(t_str **buf, char **str)
{
	int		i;

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
	int			i;

	i = -1;
	if (ft_strlen((*env)->s) == 1 && (*env)->s[0] == '?')
	{
		while (g_str[++i])
			push_str(*buf, g_str[i]);
		free_str(*env);
		return (0);
	}
	else if (ft_strlen((*env)->s) == 1 && (*env)->s[0] == '~')
	{
		clear_str(*env);
		push_str(*env, 'H');
		push_str(*env, 'O');
		push_str(*env, 'M');
		push_str(*env, 'E');
		return (1);
	}
	return (1);
}

void	make_env_buf(t_str **buf, t_str **env, char **envp)
{
	int		i;
	int		env_num;

	i = -1;
	while (envp[++i])
	{
		env_num = get_env_num(envp[i]);
		if (ft_strncmp((*env)->s, envp[i], \
						ft_max(ft_strlen((*env)->s), env_num)) == 0)
		{
			envp[i] += env_num + 1;
			while (*(envp[i])++)
				push_str((*buf), *envp[i]);
			(*buf)->len -= 1;
			break ;
		}
	}
}
