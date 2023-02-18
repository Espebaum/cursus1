/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_y3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark < gyopark@student.42seoul.kr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 19:30:06 by youngski          #+#    #+#             */
/*   Updated: 2023/02/18 18:13:02 by youngski         ###   ########.fr       */
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

char	**call_next(char *line_temp, char **ret, char *line, int i)
{
	int		j;
	int		count_i;
	int		index;

	init_split(&i, &j, line, &line_temp);
	j = 0;
	while (line_temp && *line_temp != 0)
	{
		index = 0;
		count_i = 0;
		while (*line_temp == ' ')
			line_temp++;
		if (*line_temp != '\"' && *line_temp != '\'')
			count_i = make_pure_word(line_temp, ret[j]);
		else if (*line_temp == '\'')
			count_i = make_inside_char_single(line_temp, ret[j], &j);
		else if (*line_temp == '\"')
			count_i = make_inside_char_double(line_temp, ret[j], &j);
		while ((line_temp && *line_temp) && index < count_i)
		{
			line_temp++;
			index++;
		}
		if (ret[j] && *ret[j] && (*line_temp == ' ' || *line_temp == 0
				|| *(line_temp - 1) == '<'))
			j++;
	}
	ret[j] = 0;
	return (ret);
}
