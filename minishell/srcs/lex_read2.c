/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_read2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark < gyopark@student.42seoul.kr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 22:08:28 by gyopark           #+#    #+#             */
/*   Updated: 2023/02/14 22:11:38 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	see_next_word_null(char **s, t_str **buf)
{
	if (*((*s) + 1) == '\0')
	{
		push_str(*buf, '$');
		(*s)++;
		return (1);
	}
	else
		return (0);
}

void	is_g_exit_code(char **s, t_str **buf, char *g_str, int i)
{
	while (g_str[++i])
		push_str(*buf, g_str[i]);
	(*s)++;
	(*s)++;
}

void	push_2str(t_str **buf, char **s)
{
	push_str(*buf, *(*s)++);
	push_str(*buf, *(*s)++);
}

void	init_fail_and_num(int *is_fail, int *num)
{
	*is_fail = 0;
	*num = 0;
}

t_token	*make_retcur(t_str *buf, t_token *cur, int is_fail)
{
	if (is_fail)
		cur = push_token(T_ERROR, buf, cur);
	else
		cur = push_token(T_WORD, buf, cur);
	return (cur);
}
