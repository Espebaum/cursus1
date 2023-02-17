/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_y6.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark < gyopark@student.42seoul.kr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 13:47:01 by youngski          #+#    #+#             */
/*   Updated: 2023/02/17 15:38:54 by gyopark          ###   ########.fr       */
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

int	count_pure_word(char *line_temp)
{
	int	sm_flag;
	int	du_flag;
	int	count;

	count = 0;
	init_pure_word(&sm_flag, &du_flag);
	while (line_temp && *line_temp)
	{
		if (*line_temp == '<')
		{
			if (*line_temp == '<')
			{
				line_temp++;
				(count)++;
			}
			line_temp++;
			(count)++;
			return (count);
		}
		if (*line_temp && *line_temp != ' ' && *line_temp != '\''
			&& *line_temp != '\"')
		{
			line_temp++;
			(count)++;
		}
		else
			return (count);
	}
	return (count);
}

char	**myfunc_split(char *line, int i, int j)
{
	char	**ret;
	char	*line_temp;
	int		index;
	int		count_i;

	line_temp = line;
	init_split(&i, &j, line, &line_temp);
	ret = (char **)malloc(sizeof(char *) * (count_space(line_temp) + 1));
	ret[count_space(line_temp)] = 0;
	index = 0;
	count_i = 0;
	/////////////////////////////
	while (line_temp && *line_temp != 0)
	{
		index = 0;
		while (*line_temp == ' ')
			line_temp++;
		if (*line_temp != '\"' && *line_temp != '\'')
			index += count_pure_word(line_temp);
		else if (*line_temp == '\'')
			index += count_inside_char_single(line_temp);
		else if (*line_temp == '\"')
			index += count_inside_char_double(line_temp);
		count_i += index;
		while ((line_temp && *line_temp) && index)
		{
			line_temp++;
			index--;
		}
		if ((*line_temp == ' ' || *line_temp == 0 || *(line_temp - 1) == '<'))
		{
			ret[j] = (char *)malloc(sizeof(char) * (count_i + 2));
			ret[j][0] = 0;
			if (*line_temp)
				count_i = 0;
			j++;
		}
	}
	//ret[j] = (char *)malloc(sizeof(char) * (count_i + 1));
	ret[j] = 0;
	return (call_next(line_temp, ret, line, 0));
}
