/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doc_syntax2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark < gyopark@student.42seoul.kr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 21:36:48 by gyopark           #+#    #+#             */
/*   Updated: 2023/02/19 18:01:43 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_quote_doc(char *str, int i, int len)
{
	if (i < 1)
		return (0);
	if (i + 2 > len - 1)
		return (0);
	if (str[i - 1] == '\"' && str[i + 2] == '\"')
		return (1);
	if (str[i - 1] == '\'' && str[i + 2] == '\'')
		return (1);
	return (0);
}

int	count_s_flag(int *in_squote, int *in_dquote, int *s_flag)
{
	if (*in_dquote != 1 && *in_squote == 0)
		*in_squote = 1;
	else
		*in_squote = 0;
	if (*in_dquote != 1)
		(*s_flag)++;
	return (0);
}

int	count_d_flag(int *in_squote, int *in_dquote, int *d_flag)
{
	if (*in_squote != 1 && *in_dquote == 0)
		*in_dquote = 1;
	else
		*in_dquote = 0;
	if (*in_squote != 1)
		(*d_flag)++;
	return (0);
}
