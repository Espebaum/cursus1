/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_tokenize.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 14:14:14 by gyopark           #+#    #+#             */
/*   Updated: 2023/01/28 17:51:32 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_word_end(char s)
{
	if (s == '|' || s == ' ' || s == '\n' || s == 0 || s == '<' || s == '>')
		return (1);
	return (0);
}

int	is_line_end(char s)
{
	if (s == '\n' || s == '\0')
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
