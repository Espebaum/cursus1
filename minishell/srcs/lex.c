/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 14:14:14 by gyopark           #+#    #+#             */
/*   Updated: 2023/01/28 16:52:48 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	g_env[100] = "home";
// 전역변수 구조체 링크드리스트로 관리하는 환경변수 목록에서 확인해야함.

char	*conv_env(char *name)
{
	(void) name;
	return g_env;
}

int	is_env_char(char s)
{
	if (('0' <= s && s <= '9') || ('a' <= s && s <= 'z') ||
			('A' <= s && s <= 'Z') || s == '_')
		return (1);
	return (0);
}

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
	push_str(buf, *(*(s++)));
	if ((*(*(s - 1)) == '<' || *(*(s - 1)) == '>') && *(*(s - 1)) == **s)
	{
		push_str(buf, *(*(s++)));
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

t_token *tokenize(char *s)
{
	t_token	*cur;
	t_str	*buf;

	cur = make_token();
	buf = make_str();
	while (*s != '\n' && *s)
	{
		if (*s == '<' || *s == '>' || *s == '|')
		{
			cur = read_pipe_redir(&s, cur, buf);
			/** if (buf->len != 0) */
			/**     cur = push_token(T_WORD, buf, cur); */
			/** push_str(buf, *(s++)); */
			/** if ((*(s - 1) == '<' || *(s - 1) == '>') && *(s - 1) == *s) */
			/** { */
			/**     push_str(buf, *(s++)); */
			/**     cur = push_token(T_REDIRECT, buf, cur); */
			/** } */
			/** else */
			/** { */
			/**     if (*(s - 1) == '|') */
			/**         cur = push_token(T_PIPE, buf, cur); */
			/**     else */
			/**         cur = push_token(T_REDIRECT, buf, cur); */
			/** } */
			s++;
		}
		else if (is_space(*s))
			s++;
		else
			cur = read_word(&s, cur, buf);
	}
	while (cur->prev)
		cur = cur->prev;
	return (cur);
}

int main(void)
{
	/** char	*cmd; */
    /**  */
	/** while (1) */
	/** { */
	/**     cmd = readline("inp> "); */
	/**     t_token *t = tokenize(cmd); */
	/**     print_token(t->next); */
	/**     free(cmd); */
	/**     free(t); */
	/** } */
	char	*line;

	line = "cat a <| \"grep a\"";
	t_token *test = tokenize(line);
	print_token(test->next);
	free(test);
	return (0);
}
