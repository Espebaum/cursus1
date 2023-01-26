/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_temp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 16:36:17 by gyopark           #+#    #+#             */
/*   Updated: 2023/01/26 16:36:37 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// tokenize 함수 문자열 -> token으로 나누는 함수
t_token *tokenize_bkp(char *s)
{
	char	buf[1024];
	/** t_token	*tmp; */
	t_token	*cur;
	int		i;
	int		j;

	cur = make_token();
	i = 0;
	j = 0;
	while (s[i] != '\n' && s[i])
	{
		if (s[i] == '<' || s[i] == '>' || s[i] == '|')
		{
			if (j != 0)
			{
				buf[j] = '\0';
				cur = push_token(T_WORD, buf, cur);
				j = 0;
			}
			buf[j] = s[i];
			if ((s[i] == '<' || s[i] == '>') && s[i + 1] == s[i])
			{
				buf[j + 1] = s[i];
				buf[j + 2] = '\0';
				cur = push_token(T_REDIRECT, buf, cur);
				++i;
			}
			else
			{
				buf[j + 1] = '\0';
				if (s[i] == '|')
					cur = push_token(T_PIPE, buf, cur);
				else
					cur = push_token(T_REDIRECT, buf, cur);
			}
		}
		else
			buf[j++] = s[i];
		++i;
	}
	buf[j] = '\0';
	cur = push_token(T_WORD, buf, cur);
	while (cur->prev)
		cur = cur->prev;
	return (cur);
}

