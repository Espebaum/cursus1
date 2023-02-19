/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doc_open2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark < gyopark@student.42seoul.kr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 14:41:07 by gyopark           #+#    #+#             */
/*   Updated: 2023/02/19 17:33:15 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_doc_next(char **doc_str, int idx)
{
	if (doc_str[idx + 1] && !ft_strncmp(doc_str[idx + 1], "<", 2))
		return (syntax_err());
	else if (doc_str[idx + 1] && !ft_strncmp(doc_str[idx + 1], ">", 2))
		return (syntax_err());
	else if (doc_str[idx + 1] && !ft_strncmp(doc_str[idx + 1], ">>", 3))
		return (syntax_err());
	else if (doc_str[idx + 1] && !ft_strncmp(doc_str[idx + 1], "<<", 3))
		return (syntax_err());
	else if (doc_str[idx + 1] && !ft_strncmp(doc_str[idx + 1], "|", 2))
		return (syntax_err());
	else if (!doc_str[idx + 1])
		return (syntax_err());
	return (0);
}

int	get_doc_count(char **doc_str)
{
	int	cnt;
	int	idx;

	if (doc_str[0][0] == '\0')
		return (1);
	idx = -1;
	cnt = 0;
	while (doc_str[++idx])
	{
		if (ft_strncmp(doc_str[idx], "<<", 3) == 0)
		{
			if (check_doc_next(doc_str, idx) == -1)
				return (-1);
			cnt++;
		}
	}
	return (cnt);
}

void	get_limiter(char **doc_str, t_doc *doc)
{
	int		idx;
	int		j;

	idx = 0;
	j = 0;
	while (doc_str[idx] && doc_str[idx + 1])
	{
		if (ft_strncmp(doc_str[idx], "<<", 2) == 0 && doc_str[idx][2] == 0)
		{
			doc->limiters[j++] = ft_strdup(doc_str[idx + 1]);
			doc->limiters[j] = NULL;
		}
		idx++;
	}
	j = 0;
}
