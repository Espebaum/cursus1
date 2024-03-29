/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_y6.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark < gyopark@student.42seoul.kr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 13:47:01 by youngski          #+#    #+#             */
/*   Updated: 2023/02/20 13:55:33 by youngski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_inside_char_double(char *line_temp)
{
	int	check_close;
	int	count;

	count = 0;
	line_temp++;
	check_close = 0;
	while (*line_temp && check_close == 0)
	{
		if (*line_temp == '\"')
		{
			check_close = 1;
			count += 2;
			line_temp++;
			return (count);
		}
		line_temp++;
		count++;
	}
	return (count);
}

int	count_inside_char_single(char *line_temp)
{
	int	check_close;
	int	count;

	count = 0;
	line_temp++;
	check_close = 0;
	while (*line_temp && check_close == 0)
	{
		if (*line_temp == '\'')
		{
			check_close = 1;
			line_temp++;
			count += 2;
			return (count);
		}
		line_temp++;
		count++;
	}
	return (count);
}

void	temp_count_plus_word(char **line_temp, int *count)
{
	(*line_temp)++;
	(*count)++;
}

int	count_pure_word(char *line_temp, int count)
{
	int	sm_flag;
	int	du_flag;

	init_pure_word(&sm_flag, &du_flag);
	while (line_temp && *line_temp)
	{
		if (*line_temp == '<')
		{
			if (*line_temp == '<')
			{
				temp_count_plus_word(&line_temp, &count);
			}
			temp_count_plus_word(&line_temp, &count);
			return (count);
		}
		if (*line_temp && *line_temp != ' ' && *line_temp != '\''
			&& *line_temp != '\"')
		{
			temp_count_plus_word(&line_temp, &count);
		}
		else
			return (count);
	}
	return (count);
}

int	myfunc_if_func(char **line_temp_, int *index, int *count_i, int count)
{
	char	*line_temp;

	line_temp = *line_temp_;
	*index = 0;
	while (*line_temp == ' ')
	{
		line_temp++;
		count++;
	}
	if (*line_temp != '\"' && *line_temp != '\'')
		*index += count_pure_word(line_temp, 0);
	else if (*line_temp == '\'')
		*index += count_inside_char_single(line_temp);
	else if (*line_temp == '\"')
		*index += count_inside_char_double(line_temp);
	*count_i += *index;
	while ((line_temp && *line_temp) && *index)
	{
		line_temp++;
		count++;
		(*index)--;
	}
	count += (*index);
	return (count);
}

char	**myfunc_split(char *line, int i, int j)
{
	char	**ret;
	char	*line_temp;
	int		index;
	int		count_i;

	line_temp = line;
	count_i = init_split(&i, &j, line, &line_temp);
	ret = (char **)malloc(sizeof(char *) * (count_space(line_temp) + 1));
	ret[count_space(line_temp)] = 0;
	while (line_temp && *line_temp != 0)
	{
		line_temp += myfunc_if_func(&line_temp, &index, &count_i, 0);
		if ((*line_temp == ' ' || *line_temp == 0 || *(line_temp - 1) == '<'))
		{
			ret[j] = (char *)malloc(sizeof(char) * (count_i + 2));
			ret[j][0] = 0;
			if (*line_temp)
				count_i = 0;
			j++;
		}
	}
	ret[j] = 0;
	return (call_next(line_temp, ret, line, 0));
}
