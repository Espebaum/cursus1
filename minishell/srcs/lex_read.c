/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex4.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 17:22:29 by gyopark           #+#    #+#             */
/*   Updated: 2023/01/28 17:23:08 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	read_env(char **s, t_str *buf)
{
	t_str	*env;
	char	*ret;

	env = make_str();
	while (is_env_char(*(++(*s))))
		push_str(env, **s);
	ret = conv_env(env->s);
	if (ret)
		while (*ret != '\0')
			push_str(buf, *ret++);
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
	printf("in squote: [%s]\n", buf->s);
	return (0);
}

int	read_word_dquote(char **s, t_str *buf)
{
	(*s)++;
	while (!is_line_end(**s) && **s != '\"')
	{
		if (**s == '$')
			read_env(s, buf);
		else
			push_str(buf, *((*s)++));
	}
	if (**s != '\"')
		return (1);
	(*s)++;
	printf("in dquote: [%s]\n", buf->s);
	return (0);
}

t_token	*read_word(char **s, t_token *cur, t_str *buf)
{
	int		is_fail;

	is_fail = 0;
	while (!is_word_end(**s))
	{
		if (**s == '$')
			read_env(s, buf);
		else if (**s == '\'')
			is_fail |= read_word_squote(s, buf);
		else if (**s == '\"')
			is_fail |= read_word_dquote(s, buf);
		else
			push_str(buf, *((*s)++));
	}
	printf("%s\n", buf->s);
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
	if ((*(*(s - 1)) == '<' || *(*(s - 1)) == '>') && *(*(s - 1)) == **s)
	{
		push_str(buf, *((*s)++));
		cur = push_token(T_REDIRECT, buf, cur);
	}
	else
	{
		if (*(*(s - 1)) == '|')
			cur = push_token(T_PIPE, buf, cur);
		else
			cur = push_token(T_REDIRECT, buf, cur);
	}
	return (cur);
}
