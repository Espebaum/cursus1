/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_read.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 17:22:29 by gyopark           #+#    #+#             */
/*   Updated: 2023/02/09 15:21:46 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	read_env(char **s, t_str *buf, char **envp, int *r_env)
{
	t_str	*env;
	int		i;
	int		env_num;
	char	*g_str;

	i = -1;
	env = make_str();
	g_str = ft_itoa(g_exit_code);
	while (!is_word_end(*(++(*s))) && **s != '\"')
	{
		if (**s == '$')
			break ;
		push_str(env, **s);
	}		
	if (ft_strlen(env->s) == 1 && env->s[0] == '?')
	{
		while (g_str[++i])
			push_str(buf, g_str[i]);
		free_str(env);
		return ;
	}
	while (envp[++i])
	{
		env_num = get_env_num(envp[i]);
		if (ft_strncmp(env->s, envp[i], ft_max(ft_strlen(env->s), env_num)) == 0)
		{
			envp[i] += env_num + 1;
			while (*(envp[i])++)
				push_str(buf, *envp[i]);
			buf->len -= 1;
			break ;
		}
	}
	(*r_env)++;
	free_str(env);
}
// 들어오는게 $$일때 처리, ($, $$, $$$, $$$$ ...)
// $일때는 str에 $, $$일때는 $$, 문자열 그대로 넣어주면 됨
// ~는 HOME으로 치환

int	read_word_squote(char **s, t_str *buf)
{
	(*s)++;
	while (!is_line_end(**s) && **s != '\'')
		push_str(buf, *((*s)++));
	if (**s != '\'')
		return (1);
	(*s)++;
	printf("in squote: [%s]\n", buf->s);
	return (0);
}

int	read_word_dquote(char **s, t_str *buf, char **envp, int *r_env)
{
	char	**temp;

	(*s)++;
	while (!is_line_end(**s) && **s != '\"')
	{
		temp = deep_copy_env(envp);
		if (**s == '$')
			read_env(s, buf, temp, r_env);
		else
			push_str(buf, *((*s)++));
	}
	if (**s != '\"')
		return (1);
	(*s)++;
	printf("in dquote: [%s]\n", buf->s);
	return (0);
}

t_token	*read_word(char **s, t_token *cur, t_str *buf, char **envp)
{
	int		is_fail;
	char	**temp;
	int		r_env;

	is_fail = 0;
	r_env = 0;
	while (!is_word_end(**s))
	{
		temp = deep_copy_env(envp);
		if (**s == '$')
			read_env(s, buf, temp, &r_env);
		else if (**s == '\'')
			is_fail |= read_word_squote(s, buf);
		else if (**s == '\"')
			is_fail |= read_word_dquote(s, buf, envp, &r_env);
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
