/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doc_syntax1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark < gyopark@student.42seoul.kr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 12:28:04 by gyopark           #+#    #+#             */
/*   Updated: 2023/02/15 21:26:59 by gyopark          ###   ########.fr       */
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

int	is_all_space(char *str)
{
	char	**spl;
	int		len;
	int		i;
	int		j;

	i = -1;
	spl = ft_split(str, '|');
	while (spl[++i])
	{
		j = 0;
		len = ft_strlen(spl[i]);
		while (spl[i][j] != '\0' && (spl[i][j] == ' ' || \
				ft_strncmp("<<", &spl[i][j], 2) == 0))
		{
			if (ft_strncmp("<<", &spl[i][j], 2) == 0)
				j++;
			j++;
			if (j == len)
				return (-1);
		}
		printf("j : %d, len : %d\n", j, len);
	}
	return (0);
}

int	doc_syntax_check(char *str, const int len, int i)
{
	int		s_flag;
	int		d_flag;
	int		in_dquote;
	int		in_squote;

	init_syntax_check(&s_flag, &d_flag, &in_dquote, &in_squote);
	if (str[0] == '|' || str[len - 1] == '|')
		return (-1);
	if (is_all_space(str) == -1)
		return (-1);
	while (++i < len)
	{
		if (str[i] == '\"')
			count_d_flag(&in_squote, &in_dquote, &d_flag);
		else if (str[i] == '\'')
			count_s_flag(&in_squote, &in_dquote, &s_flag);
	}
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
			if (doc_syntax_check(str, len, -1) == -1)
				return (-1);
			return (is_doc);
		}
	}
	return (is_doc);
}
