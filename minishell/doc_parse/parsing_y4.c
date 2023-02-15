/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_y4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark < gyopark@student.42seoul.kr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 19:45:46 by youngski          #+#    #+#             */
/*   Updated: 2023/02/15 19:00:59 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	redirection_count(int *i, int *count, char *line_temp)
{
	if (line_temp[*i] == '>' || line_temp[*i] == '<')
	{
		if (line_temp[(*i) + 1] == '>')
		{
			(*i)++;
			(*count)++;
		}
		else if (line_temp[(*i) + 1] == '<')
		{
			(*i)++;
			(*count)++;
		}
		(*i)++;
		(*count)++;
		return (1);
	}
	return (0);
}

void	part_make_line(int *i, int *j, int *count, char **line_temp)
{
	*j += 1;
	*count = 0;
	*line_temp += *i;
	*i = 0;
}
