/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_env1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark < gyopark@student.42seoul.kr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 16:25:16 by gyopark           #+#    #+#             */
/*   Updated: 2023/02/14 12:06:11 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*flip_meta_chr(char *ret)
{
	int		len;
	int		r_len;
	int		i;
	char	*temp;

	i = -1;
	len = ft_strlen(ret);
	r_len = len;
	temp = (char *)malloc(sizeof(char) * (len + 1));
	temp[len] = '\0';
	while (++i < len)
	{
		temp[i] = ret[--r_len];
	}
	free(ret);
	return (temp);
}

char	*make_meta_chr(char *ret, int *size, char meta_chr)
{
	int		i;
	char	*temp_ret;

	i = -1;
	temp_ret = ret;
	ret = (char *)malloc(sizeof(char) * ++(*size));
	ret[(*size) - 1] = '\0';
	while (temp_ret[++i])
		ret[i] = temp_ret[i];
	ret[i] = meta_chr;
	return (ret);
}

char	*check_meta_chr(t_str **env)
{
	char	*str;
	int		len;
	int		i;
	char	*ret;
	int		size;

	size = 1;
	ret = ft_strdup("");
	i = -1;
	len = ft_strlen((*env)->s);
	if (is_meta_chr((*env)->s[len - 1]) == 1)
	{
		while (is_meta_chr((*env)->s[--len]) == 1)
			ret = make_meta_chr(ret, &size, (*env)->s[len]);
	}
	else
		return (NULL);
	ret = flip_meta_chr(ret);
	str = (char *)malloc(sizeof(char) * (len + 1));
	str[len] = '\0';
	while (++i < len + 1)
		str[i] = (*env)->s[i];
	clear_str(*env);
	i = -1;
	while (++i < len + 1)
		push_str(*env, str[i]);
	free(str);
	return (ret);
}

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

int	make_env_buf(t_str **buf, t_str **env, char **envp, char *meta_str)//환경변수 없으면 메타문자 buf에 가져다붙여야함
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
			(*buf)->len -= 1;
			return (1);
		}
	}
	i = -1;
	if (meta_str)
		return (1);
	return (0);
}
