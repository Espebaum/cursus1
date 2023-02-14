/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_y2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 19:22:14 by youngski          #+#    #+#             */
/*   Updated: 2023/02/14 16:10:43 by youngski         ###   ########.fr       */
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

void	copy_bef_smlimiter(int *i, int *count, char *line_temp, char *ret)
{
	(*i)++;
	while (line_temp[*i] != '\'')
	{
		ret[*count] = line_temp[*i];
		ret[(*count) + 1] = 0;
		(*i)++;
		(*count)++;
	}
	(*i)++;
}

void	copy_bef_lglimiter(int *i, int *count, char *line_temp, char *ret)
{
	(*i)++;
	while (line_temp[*i] != '\"')
	{
		ret[*count] = line_temp[*i];
		ret[(*count) + 1] = 0;
		(*i)++;
		(*count)++;
	}

	(*i)++;
}
void	make_pure_word(int *i, int *count, char *line_temp, char *ret)
{
	int	sm_flag;
	int	du_flag;

	sm_flag = 0;
	du_flag = 0;
	while (line_temp && line_temp[*i])
	{
		if (line_temp[*i] == '\'')
		{
			copy_bef_smlimiter(i,count,line_temp,ret);
			continue ;
		}
		if (line_temp[*i] == '\"')
		{
			copy_bef_lglimiter(i,count,line_temp,ret);
			continue ;
		}
		if (line_temp[*i] != ' ')
		{
			ret[*count] = line_temp[*i];
			ret[(*count) + 1] = 0;
			(*i)++;
			(*count)++;
		}
		else
			return ;
	}
}
