/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 14:14:14 by gyopark           #+#    #+#             */
/*   Updated: 2023/01/26 21:05:05 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

typedef struct str
{
	int		len;
	int		capacity;
	char	*s;
}	t_str;

t_str	*make_str(void)
{
	t_str	*ret;

	ret = (t_str *) malloc(sizeof(t_str));
	ret->capacity = 32;
	ret->len = 0;
	ret->s = (char *) malloc(sizeof(char) * ret->capacity);
	ret->s[0] = '\0';
	return ret;
}

void	resize_str(t_str *str)
{
	char	*tmp;
	int		i;

	tmp = (char *) malloc(sizeof(char) * str->capacity * 2);
	i = -1;
	while (++i < str->len)
		tmp[i] = str->s[i];
	free(str->s);
	str->s = tmp;
	str->capacity *= 2;
}

void 	push_str(t_str *str, char val)
{
	if (str->capacity - 1 == str->len)
	{
		resize_str(str);
	}
	str->s[str->len++] = val;
	str->s[str->len] = '\0';
}

void	free_str(t_str *str)
{
	free(str->s);
	free(str);
}

void	clear_str(t_str *str)
{
	free(str->s);
	str->s = (char *) malloc(sizeof(char) * str->capacity);
	str->len = 0;
	str->s[0] = '\0';
}

typedef struct s_token
{
	int				type;
	char			*str;
	struct s_token  *prev;
	struct s_token  *next;
}	t_token;

t_token	*make_token(void)
{
	t_token *t;

	t = (t_token *) malloc(sizeof(t_token));
	t->type = 0;
	t->str = 0;
	t->prev = 0;
	t->next = 0;
	return (t);
}

t_token	*push_token(int type, t_str *str, t_token *prev)
{
	t_token	*t;

	t = make_token();
	t->type = type;
	t->str = strdup(str->s);
	clear_str(str);
	prev->next = t;
	t->prev = prev;
	return (t);
}

int	is_word_end(char s)
{
	if (s == '|' || s == ' ' || s =='\n' || s == 0 || s == '<' || s == '>')
		return (1);
	return (0);
}

int is_line_end(char s)
{
	if (s == '\n' || s == '\0')
		return 1;
	return 0;
}

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
		return 1;
	return 0;
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
	int		is_fail;

	(*s)++;
	while (!is_line_end(**s) || **s != '\'')
		push_str(buf, *((*s)++));
	is_fail = (**s != '\'');
	(*s)++;
	printf("in squote: [%s]\n", buf->s);
	return (is_fail);
}

int	read_word_dquote(char **s, t_str *buf)
{
	int		is_fail;

	(*s)++;
	while (!is_line_end(**s) || **s != '\"')
	{
		if (**s == '$')
			read_env(s, buf);
		else
			push_str(buf, *((*s)++));
	}
	is_fail = (**s != '\"');
	(*s)++;
	return (is_fail);
}
t_token	*read_word(char **s, t_token *t, t_str *buf)
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
	if(is_fail)
		t = push_token(T_ERROR, buf, t);
	else
		t = push_token(T_WORD, buf, t);
	return (t);
}

int	is_space(char c)
{
	if (c == ' ')
		return 1;
	return 0;
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
			if (buf->len != 0)
				cur = push_token(T_WORD, buf, cur);
			push_str(buf, *(s++));
			if ((*(s - 1) == '<' || *(s - 1) == '>') && *(s - 1) == *s)
			{
				push_str(buf, *(s++));
				cur = push_token(T_REDIRECT, buf, cur);
			}
			else
			{
				if (*(s - 1) == '|')
					cur = push_token(T_PIPE, buf, cur);
				else
					cur = push_token(T_REDIRECT, buf, cur);
			}
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

void print_token(t_token *cur)
{
	while (cur)
	{
		printf("type: %d\n", cur->type);
		printf("value: %s\n", cur->str);
		cur = cur->next;
	}
}

int main(void)
{
	char	*line;

	line = readline("");
	t_token *t = tokenize(line);
	print_token(t->next);
	return (0);
}
