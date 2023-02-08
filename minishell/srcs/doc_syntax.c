/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doc_syntax.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 12:28:04 by gyopark           #+#    #+#             */
/*   Updated: 2023/02/08 23:01:13 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	doc_syntax_check(char *str, const int len)
{
	int		i;
	int		s_flag;
	int		d_flag;

	i = -1;
	s_flag = 0;
	d_flag = 0;
	if (str[0] == '|' || str[len - 1] == '|')
		return (-1);
	while (++i < len)
	{
		if (str[i] == '\"')
			d_flag++;
		if (str[i] == '\'')
			s_flag++;
	}
	if ((s_flag % 2 == 1) || (d_flag % 2 == 1))
		return (-1);
	return (0);
}
//"b'c"는 b'c가 리미터, 'b"c'는 b"c가 리미터이므로 단순히 홀짝 비교만 하면 안된다.

int	doc_syntax(char *str)
{
	const int	len = ft_strlen(str);
	int			i;

	i = -1;
	while (++i < len - 1)
	{
		if (str[i] == '<' && str[i + 1])
			if (doc_syntax_check(str, len) == -1)
				return (-1);
	}
	return (0);
}