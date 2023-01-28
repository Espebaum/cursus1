/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_tokenize.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 14:14:14 by gyopark           #+#    #+#             */
/*   Updated: 2023/01/28 17:46:43 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	g_env[100] = "home";
// 전역변수 구조체 링크드리스트로 관리하는 환경변수 목록에서 확인해야함.

char	*conv_env(char *name)
{
	(void) name;
	return (g_env);
}

int	is_env_char(char s)
{
	if (('0' <= s && s <= '9') || ('a' <= s && s <= 'z')
		|| ('A' <= s && s <= 'Z') || s == '_')
		return (1);
	return (0);
}

t_token	*tokenize(char *s)
{
	t_token	*cur;
	t_str	*buf;

	cur = make_token();
	buf = make_str();
	while (*s != '\n' && *s)
	{
		if (*s == '<' || *s == '>' || *s == '|')
			cur = read_pipe_redir(&s, cur, buf);
		else if (is_space(*s))
			s++;
		else
			cur = read_word(&s, cur, buf);
	}
	while (cur->prev)
		cur = cur->prev;
	return (cur);
}

int	main(void)
{
	char	*cmd;
	t_token	*t;

	while (1)
	{
		cmd = readline("inp> ");
		t = tokenize(cmd);
		print_token(t->next);
		free(cmd);
		free(t);
	}
	return (0);
}
