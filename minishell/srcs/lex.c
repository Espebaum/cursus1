/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 14:14:14 by gyopark           #+#    #+#             */
/*   Updated: 2023/01/26 16:41:11 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

typedef struct  s_token
{
	int		type;
	char	*str;
	struct s_token  *prev;
	struct s_token  *next;
}   t_token;

t_token *make_token(void)
{
	t_token *t;

	t = (t_token *) malloc(sizeof(t_token));
	t->type = 0;
	t->str = 0;
	t->prev = 0;
	t->next = 0;
	return (t);
}

t_token *push_token(int type, char *str, t_token *prev)
{
	t_token	*t;
	/** char	*c; */
	/** int		i; */

	t = make_token();
	t->type = type;
	t->str = strdup(str);
	prev->next = t;
	t->prev = prev;
	return (t);
}

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
	if (str->capacity == str->len)
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

int	is_word_end(char s)
{
	if (s == '|' || s == ' ' || s == '\n' || s == 0)
		return (1);
	return (0);
}

t_token	*read_single_quote(char **s, t_token *t)
{
	t_str	*buf;
	int		is_fail;

	return (t);
}

t_token	*read_double_quote(char **s, t_token *t)
{
	t_str	*buf;
	int		is_fail;

	return (t);
}

t_token	*read_word(char **s, t_token *t)
{
	t_str	*buf;
	int		is_fail;

	is_fail = 0;
	buf = make_str();
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
	if (is_fail)
		t = push_token(T_ERROR, "", t);
	else
		t = push_token(T_WORD, buf->s, t);
	free_str(buf);
	return (t);
}

t_token *tokenize(char *s)
{
	t_token	*cur;

	cur = make_token();
	while (1)
	{
		if (*s == '\n' || *s == '\0')
			break ;
		cur = read_word(&s, cur);
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
	char cmd[] = "echo 123>a";
	t_token *t = tokenize(cmd);
	print_token(t->next);
	return (0);
}
