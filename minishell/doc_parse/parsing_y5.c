/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_y5.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark < gyopark@student.42seoul.kr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 21:42:48 by gyopark           #+#    #+#             */
/*   Updated: 2023/02/15 19:01:00 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	redirection_split(int *i, int *count, char *line_temp, char *ret)
{
	if (line_temp[*i] == '>' || line_temp[*i] == '<')
	{
		if (line_temp[(*i) + 1] == '>')
		{
			ret[*count] = line_temp[*i];
			ret[(*count) + 1] = 0;
			(*i)++;
			(*count)++;
		}
		else if (line_temp[(*i) + 1] == '<')
		{
			ret[*count] = line_temp[*i];
			ret[(*count) + 1] = 0;
			(*i)++;
			(*count)++;
		}
		ret[*count] = line_temp[*i];
		ret[(*count) + 1] = 0;
		(*i)++;
		(*count)++;
		return (0);
	}
	return (1);
}

int	pipe_split(int *i, int *count, char *line_temp, char *ret)
{
	if (line_temp[*i] == '|')
	{
		ret[*count] = line_temp[*i];
		ret[(*count) + 1] = 0;
		(*i)++;
		(*count)++;
		return (0);
	}
	return (1);
}
