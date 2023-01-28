/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 13:24:14 by gyopark           #+#    #+#             */
/*   Updated: 2023/01/28 15:03:11 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_str	*make_str(void)
{
	t_str	*ret;

	ret = (t_str *) malloc(sizeof(t_str));
	ret->capacity = 32;
	ret->len = 0;
	ret->s = (char *) malloc(sizeof(char) * ret->capacity);
	ret->s[0] = '\0';
	return (ret);
}

void	push_str(t_str *str, char val)
{
	if (str->capacity - 1 == str->len)
	{
		resize_str(str);
	}
	str->s[str->len++] = val;
	str->s[str->len] = '\0';
}

t_token	*make_token(void)
{
	t_token	*t;

	t = (t_token *) malloc(sizeof(t_token));
	t->type = 0;
	t->str = 0;
	t->prev = 0;
	t->next = 0;
	return (t);
}

t_token	*push_token(int type, t_str *buf, t_token *prev)
{
	t_token	*next;

	next = make_token();
	next->type = type;
	next->str = strdup(buf->s);
	clear_str(buf);
	prev->next = next;
	next->prev = prev;
	return (next);
}

int	is_space(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	return (0);
}
/** 문자열과 토큰 타입에 대한 구조체 */
/** typedef struct str */
/** { */
/**     int		len; */
/**     int		capacity; */
/**     char	*s; */
/** }	t_str; */
/**  */
/** typedef struct  s_token */
/** { */
/**     int		type; */
/**     char	*str; */
/**     struct s_token  *prev; */
/**     struct s_token  *next; */
/** }   t_token; */