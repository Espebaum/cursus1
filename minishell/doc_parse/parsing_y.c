/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_y.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 19:15:04 by youngski          #+#    #+#             */
/*   Updated: 2023/02/11 13:01:31 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_space(char *line)
{
	int	len;
	int	cnt;
	int	i;

	len = ft_strlen(line);
	i = -1;
	cnt = 0;
	while (++i < len - 1)
	{
		if (line[i] == ' ' || line[i] == '<' \
				|| line[i] == '>' || line[i] == '|')
		{
			if (line[i + 1] == '<' || line[i + 1] == '>')
				i++;
			cnt++;
			i++;
		}
		while (line[i] == ' ')
			i++;
	}
	return (cnt + 2);
}

void	count_inside_char(int *i, int *count, \
		char *line_temp, char my_char)
{
	int	temp;

	(*i)++;
	while (line_temp && line_temp[*i])
	{
		if (line_temp[*i] != my_char)
		{
			(*i)++;
			(*count)++;
		}
		else
		{
			(*i)++;
			temp = (*i);
			return ;
		}
	}
}

void	make_inside_char_double(int *i, int *count, char *line_temp, char *ret)
{
	int	temp;

	(*i)++;
	while (line_temp && line_temp[*i])
	{
		if (line_temp[*i] != '\"')
		{
			ret[*count] = line_temp[*i];
			ret[(*count) + 1] = 0;
			(*i)++;
			(*count)++;
		}
		else
		{
			(*i)++;
			temp = (*i);
			return ;
		}
	}
}

void	make_inside_char_single(int *i, int *count, char *line_temp, char *ret)
{
	int	temp;

	(*i)++;
	while (line_temp && line_temp[*i])
	{
		if (line_temp[*i] != '\'')
		{
			ret[*count] = line_temp[*i];
			ret[(*count) + 1] = 0;
			(*i)++;
			(*count)++;
		}
		else
		{
			(*i)++;
			temp = (*i);
			return ;
		}
	}
}
