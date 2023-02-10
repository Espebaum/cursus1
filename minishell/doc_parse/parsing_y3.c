/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_y3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 19:30:06 by youngski          #+#    #+#             */
/*   Updated: 2023/02/10 16:40:11 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_split(int *i, int *j, char *line, char **line_temp)
{
	*line_temp = line;
	*i = 0;
	*j = 0;
}

int	skip_space(int *i, char **line_temp)
{
	if (!(*line_temp))
		return (1);
	while ((*line_temp) && *line_temp[*i] == ' ')
		(*line_temp)++;
	if (!(*line_temp) || *line_temp[*i] == 0)
		return (1);
	return (0);
}

int	count_split_len(char **line_temp, int *i, int *count)
{
	if (!(*line_temp) && !(*line_temp)[*i])
		return (1);
	if ((*line_temp)[*i] != '\"' && *line_temp[*i] != '\'')
		count_pure_word(i, count, line_temp[*i]);
	else
	{
		if (*line_temp[*i] == '\'')
			count_inside_char(i, count, line_temp[*i], '\'');
		else if (*line_temp[*i] == '\"')
			count_inside_char(i, count, line_temp[*i], '\"');
	}
	return (0);
}

char	**myfunc_split(char *line, int i, int j, int count)
{
	char	**ret;
	char	*line_temp;

	init_split(&i, &j, line, &line_temp);
	count = 0;
	ret = (char **)malloc(sizeof(char *) * (count_space(line_temp) + 1));
	ret[count_space(line_temp)] = 0;
	while (line_temp && line_temp[i])
	{
		if (skip_space(&i, &line_temp))
			return (ret);
		while (line_temp && line_temp[i] != 0 && line_temp[i] != ' ')
		{
			if (count_split_len(&line_temp, &i, &count))
				return (ret);
			ret[j] = (char *)malloc(sizeof(char) * (count + 1));
			ret[j++][count] = 0;
			count = 0;
			line_temp += i;
			i = 0;
		}
	}
	return (call_next(line_temp, ret, line, 0));
}

char	**call_next(char *line_temp, char **ret, char *line, int i)
{
	int	j;
	int	count;

	init_split(&i, &j, line, &line_temp);
	while (line_temp && line_temp[i])
	{
		if (skip_space(&i, &line_temp))
			return (ret);
		while (line_temp && line_temp[i] != 0 && line_temp[i] != ' ')
		{
			if (line_temp[i] != '\"' && line_temp[i] != '\'')
				make_pure_word(&i, &count, &line_temp[i], ret[j]);
			else
			{
				if (line_temp[i] == '\'')
					make_inside_char_single(&i, &count, &line_temp[i], ret[j]);
				else if (line_temp[i] == '\"')
					make_inside_char_double(&i, &count, &line_temp[i], ret[j]);
			}
			part_make_line(&i, &j, &count, &line_temp);
		}
	}
	ret[j] = 0;
	return (ret);
}
