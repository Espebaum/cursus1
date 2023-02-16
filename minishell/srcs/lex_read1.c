/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_read1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark < gyopark@student.42seoul.kr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 17:22:29 by gyopark           #+#    #+#             */
/*   Updated: 2023/02/16 20:43:16 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	read_word_squote(char **s, t_str *buf)
{
	(*s)++;
	while (!is_line_end(**s) && **s != '\'')
		push_str(buf, *((*s)++));
	if (**s != '\'')
		return (1);
	(*s)++;
	return (0);
}

int	read_word_dquote(char **s, t_str *buf, char **envp)
{
	char	**temp;

	(*s)++;
	while (!is_line_end(**s) && **s != '\"')
	{
		temp = deep_copy_env(envp);
		if (**s == '$')
			read_env(s, buf, temp);
		else
			push_str(buf, *((*s)++));
	}
	if (**s != '\"')
		return (1);
	(*s)++;
	return (0);
}

int	read_env(char **s, t_str *buf, char **temp)
{
	t_str	*env;
	char	*g_str;
	char	*meta_str;

	env = make_str();
	g_str = ft_itoa(g_exit_code);
	if (see_next_word_null(s, &buf) == 1)
	{
		free(g_str);
		free_str(env);
		return (1);
	}
	if (see_next_word_meta(s, &buf, g_str) == 1)
	{
		free(g_str);
		free_str(env);
		return (1);
	}
	(*s)++;
	while (!is_word_end(**s) && **s != '\"')
	{
		if (**s == '$')
			break ;
		push_str(env, **s);
		(*s)++;
	}
	meta_str = check_meta_chr(&env, 0, 0, 0);
	if (make_env_buf(&buf, &env, temp, meta_str) == 0)
	{
		free(g_str);
		return (0);
	}
	free_meta_str(meta_str, &env, buf);
	free(g_str);
	return (1);
}

t_token	*read_word(char **s, t_token *cur, t_str *buf, char **envp)
{
	int		is_fail;
	int		num;
	char	**temp;

	init_fail_and_num(&is_fail, &num);
	while (!is_word_end(**s))
	{
		if (**s == '$')
		{
			temp = deep_copy_env(envp);
			if (read_env(s, buf, temp) == 0)
			{
				if (buf->s[0] != '\0')
					push_token(T_WORD, buf, cur);
				else
					buf->null_flag = 1;
				free_spl(temp);
				return (cur);
			}
			free_spl(temp);
		}
		else if (**s == '\'')
			is_fail |= read_word_squote(s, buf);
		else if (**s == '\"')
			is_fail |= read_word_dquote(s, buf, envp);
		else
			push_str(buf, *((*s)++));
	}
	return (make_retcur(buf, cur, is_fail));
}

t_token	*read_pipe_redir(char **s, t_token *cur, t_str *buf)
{
	if (buf->len != 0)
		cur = push_token(T_WORD, buf, cur);
	push_str(buf, *((*s)++));
	if ((*(*(s)-1) == '<' || *(*(s)-1) == '>') && *(*(s) - 1) == **s)
	{
		push_str(buf, *((*s)++));
		cur = push_token(T_REDIRECT, buf, cur);
	}
	else
	{
		if (*(*(s) - 1) == '|')
			cur = push_token(T_PIPE, buf, cur);
		else
			cur = push_token(T_REDIRECT, buf, cur);
	}
	return (cur);
}
