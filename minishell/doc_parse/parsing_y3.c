/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_y3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark < gyopark@student.42seoul.kr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 19:30:06 by youngski          #+#    #+#             */
/*   Updated: 2023/02/15 19:01:24 by gyopark          ###   ########.fr       */
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

/*
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
*/

void	count_inside_char_single(char *line_temp, char *ret)
{
	int	check_close;
	int	count;

	while (*ret)
		ret++;
	count = 0;
	line_temp++;
	check_close = 0;
	while (*line_temp && check_close == 0)
	{
		if (*line_temp == '\'')
		{
			check_close = 1;
			line_temp++;
			break ;
		}
		line_temp++;
		count++;
	}
	ret = (char *)malloc(sizeof(char) * (count + 1));
}

char	**myfunc_split(char *line, int i, int j, int count_i)
{
	char	**ret;
	char	*line_temp;
	int		index;

	line_temp = line;
	init_split(&i, &j, line, &line_temp);
	ret = (char **)malloc(sizeof(char *) * (count_space(line_temp) + 1));
	ret[count_space(line_temp)] = 0;
	index = 0;
	while (index <= count_space(line_temp))
	{
		ret[index] = (char *)malloc(sizeof(char) * (1000));
		ret[index][0] = 0;
		ret[index + 1] = 0;
		index++;
	}
	return (call_next(line_temp, ret, line, 0));
}

char	**call_next(char *line_temp, char **ret, char *line, int i)
{
	int		j;
	char	*for_free;
	int		count_i;
	int		index;
	int		asdf;

	for_free = line_temp;
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
			count_i = make_inside_char_single(line_temp, ret[j]);
		else if (*line_temp == '\"')
			count_i = make_inside_char_double(line_temp, ret[j]);
		while ((line_temp && *line_temp) && index < count_i)
		{
			line_temp++;
			index++;
		}
		if (ret[j] && *ret[j] && (*line_temp == ' ' || *line_temp == 0
				|| *(line_temp - 1) == '<'))
		{
			j++;
			ret[j][0] = 0;
		}
	}
	asdf = -1;
	ret[j + 1] = 0;
	while (ret[++asdf])
		printf("ret[%d] = %s\n", asdf, ret[asdf]);
	return (ret);
}
