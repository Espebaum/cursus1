/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_env3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark < gyopark@student.42seoul.kr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 22:06:26 by gyopark           #+#    #+#             */
/*   Updated: 2023/02/14 22:11:40 by gyopark          ###   ########.fr       */
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

char	*check_meta_chr(t_str **env, int i, int len, int size)
{
	char	*str;
	char	*ret;

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

void	free_meta_str(char *meta_str, t_str *env, t_str *buf)
{
	int	i;

	i = -1;
	if (meta_str)
		while (meta_str[++i])
			push_str(buf, meta_str[i]);
	if (meta_str)
		free(meta_str);
	if (env->s)
		free_str(env);
}

int	see_next_word_meta(char **s, t_str **buf, t_str **env, char *g_str)
{
	if (*((*s) + 1) != '\0' && is_meta_chr(*((*s) + 1)) == 1)
	{
		if (*((*s) + 1) == '?')
			is_g_exit_code(s, buf, g_str, -1);
		else if (*((*s) + 1) == '\'')
		{
			(*s)++;
			while (!is_word_end(**s) && **s != '\'')
				push_str(*buf, *(*s)++);
			return (1);
		}
		else if (*((*s)++ + 1) == '\"')
			return (1);
		else
			push_2str(buf, s);
		while (1)
		{
			if (**s == '$' || **s == '\0')
				return (1);
			push_str(*buf, (*(*s)++));
		}
	}
	return (0);
}
