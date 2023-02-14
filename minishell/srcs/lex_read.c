/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_read.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark < gyopark@student.42seoul.kr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 17:22:29 by gyopark           #+#    #+#             */
/*   Updated: 2023/02/14 14:46:36 by gyopark          ###   ########.fr       */
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
			read_env(s, buf, temp, 0);
		else
			push_str(buf, *((*s)++));
	}
	if (**s != '\"')
		return (1);
	(*s)++;
	return (0);
}

int	see_next_word_null(char **s, t_str **buf)
{
	if (*((*s) + 1) == '\0')
	{
		push_str(*buf, '$');
		(*s)++;
		return (1);
	}
	else
		return (0);
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
	int		i;

	i = -1;
	if (*((*s) + 1) != '\0' && is_meta_chr(*((*s) + 1)) == 1)
	{
		if (*((*s) + 1) == '?')
		{
			while (g_str[++i])
				push_str(*buf, g_str[i]);
			(*s)++;
			(*s)++;
		}
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
		{
			push_str(*buf, *(*s)++);
			push_str(*buf, *(*s)++);
		}
		while (1)
		{
			if (**s == '$' || **s == '\0')
				return (1);
			push_str(*buf, (*(*s)++));
		}
	}
	return (0);
}

int	read_env(char **s, t_str *buf, char **envp, char **temp)
{
	t_str	*env;
	char	*g_str;
	char	*meta_str;
	char	*t;

	env = make_str();
	g_str = ft_itoa(g_exit_code);
	if (see_next_word_null(s, &buf) == 1)
		return (1);
	if (see_next_word_meta(s, &buf, &env, g_str) == 1)
		return (1);
	while (!is_word_end(*(++(*s))) && **s != '\"')
	{
		if (**s == '$')
			break ;
		push_str(env, **s);
	}
	meta_str = check_meta_chr(&env, 0, 0, 0);
	temp = deep_copy_env(envp);
	if (make_env_buf(&buf, &env, temp, meta_str) == 0)
		return (0);
	free_meta_str(meta_str, env, buf);
	free(g_str);
	free(temp);
	return (1);
}

void	init_fail_and_num(int *is_fail, int *num)
{
	*is_fail = 0;
	*num = 0;
}

t_token *make_retcur(t_str *buf, t_token *cur, int is_fail)
{
	if (is_fail)
		cur = push_token(T_ERROR, buf, cur);
	else
		cur = push_token(T_WORD, buf, cur);
	return (cur);
}

t_token	*read_word(char **s, t_token *cur, t_str *buf, char **envp)
{
	int		is_fail;
	int		num;

	init_fail_and_num(&is_fail, &num);
	while (!is_word_end(**s))
	{
		if (**s == '$')
		{
			if (read_env(s, buf, envp, 0) == 0)
			{
				if (buf->s[0] != '\0')
					push_token(T_WORD, buf, cur);
				return (cur);
			}
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
		if (*(*(s) - 1) == '<')
			cur->flag = 1;
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
