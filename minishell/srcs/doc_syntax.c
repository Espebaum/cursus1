/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doc_syntax.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark < gyopark@student.42seoul.kr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 12:28:04 by gyopark           #+#    #+#             */
/*   Updated: 2023/02/14 14:46:15 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	init_syntax_check(int *s_flag, int *d_flag, int *in_dquote, int *in_squote)
{
	*s_flag = 0;
	*d_flag = 0;
	*in_dquote = 0;
	*in_squote = 0;
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

int	doc_syntax_check(char *str, const int len)
{
	int		i;
	int		s_flag;
	int		d_flag;
	int		in_dquote;
	int		in_squote;

	i = -1;
	init_syntax_check(&s_flag, &d_flag, &in_dquote, &in_squote);
	if (str[0] == '|' || str[len - 1] == '|')
		return (-1);
	while (++i < len)
	{
		if (str[i] == '\"')
			count_d_flag(&in_squote, &in_dquote, &d_flag);
		else if (str[i] == '\'')
			count_s_flag(&in_squote, &in_dquote, &s_flag);
	}
	printf("s_flag : %d d_flag : %d\n", s_flag, d_flag);
	if ((s_flag % 2 == 1) || (d_flag % 2 == 1))
		return (-1);
	return (0);
}

int	doc_syntax(char *str)
{
	const int	len = ft_strlen(str);
	int			i;
	int			is_doc;

	is_doc = 0;
	i = -1;
	while (++i < len - 1)
	{
		if (str[i] == '<' && str[i + 1] == '<')
		{
			is_doc = 1;
			if (doc_syntax_check(str, len) == -1)
				return (-1);
			return (is_doc);
		}
	}
	return (is_doc);
}
