/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_env3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark < gyopark@student.42seoul.kr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 22:06:26 by gyopark           #+#    #+#             */
/*   Updated: 2023/02/16 15:28:05 by gyopark          ###   ########.fr       */
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
	char	*tmp_str;
	char	*ret;
	char	*str;
	int		idx;
	int		tmp;

	idx = -1;
	tmp_str = (*env)->s;
	while (*tmp_str)
	{
		if (is_meta_chr(*tmp_str) == 1)
			break ;
		tmp_str++;
		if (*tmp_str == '\0')
			return (NULL);
	}
	len = ft_strlen((*env)->s); // $HO..ME -> len 6
	while ((*env)->s[i])
	{
		if (is_meta_chr((*env)->s[i++]) != 1)
			if (is_meta_chr((*env)->s[i]) == 1)
				break ; // i 2
	}
	size = len - i; // size 4
	str = (char *)malloc(sizeof(char) * (i + 1)); //3칸
	str[i] = '\0';
	ret = (char *)malloc(sizeof(char) * (size + 1)); //5칸
	ret[size] = '\0'; // ret[4] NULL
	while (++idx < i)
		str[idx] = (*env)->s[idx]; // 환경변수 부분 채워줌
	idx = -1;
	tmp = i;
	while (++idx < size) // 0 < 4
		ret[idx] = (*env)->s[i++]; // ret : 환경변수 이후 부분 채워줌
	clear_str(*env);
	idx = -1;
	while (++idx < tmp)
		push_str(*env, str[idx]);
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

int	see_next_word_meta(char **s, t_str **buf, char *g_str)
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
		else if (*((*s) + 1) == '\"')
		{
			(*s)++;
			return (1);
		}
		else
			push_2str(buf, s);
		while (**s)
		{
			if (**s == '\0' || **s == '$')
				return (1);
			push_str(*buf, (**s));
			(*s)++;
		}
	}
	return (0);
}
