/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_read.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark < gyopark@student.42seoul.kr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 17:22:29 by gyopark           #+#    #+#             */
/*   Updated: 2023/02/11 14:50:00 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	read_env(char **s, t_str *buf, char **envp)
{
	t_str		*env;
	int			i;
	char		*g_str;
	char		*meta_str;

	i = -1;
	env = make_str();
	g_str = ft_itoa(g_exit_code);
	if (*((*s) + 1) == '\0' || *((*s) + 1) == '$')
		if (check_all_dollar(&buf, s) == 0)
			return ;
	while (!is_word_end(*(++(*s))) && **s != '\"')
	{
		if (**s == '$')
			break ;
		push_str(env, **s);
	}
	if (env_read(&buf, &env, g_str) == 0)
		return ;
	meta_str = check_meta_chr(&env);
	make_env_buf(&buf, &env, envp);
	i = -1;
	if (meta_str)
		while (meta_str[++i])
			push_str(buf, meta_str[i]);
	if (meta_str)
		free(meta_str);
	free_str(env);
}

void	read_d_env(char **s, t_str *buf, char **envp)
{
	t_str		*env;
	int			i;
	char		*g_str;
	char		*meta_str;

	i = -1;
	env = make_str();
	g_str = ft_itoa(g_exit_code);
	if (*((*s) + 1) == '\0' || *((*s) + 1) == '$')
		if (check_all_dollar(&buf, s) == 0)
			return ;
	while (!is_word_end(*(++(*s))) && **s != '\"')
	{
		if (**s == '$')
			break ;
		push_str(env, **s);
	}
	if (env_read(&buf, &env, g_str) == 0)
		return ;
	meta_str = check_meta_chr(&env);
	make_env_buf(&buf, &env, envp);
	i = -1;
	if (meta_str)
		while (meta_str[++i])
			push_str(buf, meta_str[i]);
	if (meta_str)
		free(meta_str);
	free_str(env);
}

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
			read_d_env(s, buf, temp);
		else
			push_str(buf, *((*s)++));
	}
	if (**s != '\"')
		return (1);
	(*s)++;
	return (0);
}

t_token	*read_word(char **s, t_token *cur, t_str *buf, char **envp)
{
	int		is_fail;
	char	**temp;

	is_fail = 0;
	while (!is_word_end(**s))
	{
		temp = deep_copy_env(envp);
		if (**s == '$')
			read_env(s, buf, temp);
		else if (**s == '\'')
			is_fail |= read_word_squote(s, buf);
		else if (**s == '\"')
			is_fail |= read_word_dquote(s, buf, envp);
		else
			push_str(buf, *((*s)++));
	}
	if (is_fail)
		cur = push_token(T_ERROR, buf, cur);
	else
		cur = push_token(T_WORD, buf, cur);
	return (cur);
}

t_token	*read_pipe_redir(char **s, t_token *cur, t_str *buf)
{
	if (buf->len != 0)
		cur = push_token(T_WORD, buf, cur);
	push_str(buf, *((*s)++));
	if ((*(*(s)- 1) == '<' || *(*(s) - 1) == '>') && *(*(s) - 1) == **s)
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
