/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_y.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark < gyopark@student.42seoul.kr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 19:15:04 by youngski          #+#    #+#             */
/*   Updated: 2023/02/12 18:27:16 by gyopark          ###   ########.fr       */
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
	int		temp;
	int		flag;
	char	t;

	if (my_char == '\"')
		t = '\'';
	else
		t = '\"';
	flag = 0;
	(*i)++;
	while (line_temp && line_temp[*i])
	{
		if (line_temp[*i + 1] != ' ' && line_temp[*i] == my_char)
		{
			if (line_temp[*i + 1] == t && flag == 1)
			{
				count_inside_char(i, count, line_temp, t);
				flag = 0;
			}
			else if (flag == 0)
				flag = 1;
			(*i)++;
			(*count)++;
		}
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
	int	check_close;

	(*i)++;
	check_close = 0;
	while (line_temp && line_temp[*i])
	{
		if (line_temp[*i + 1] != ' ' && line_temp[*i] == '\"')
		{
			(*i)++;
			if (line_temp[*i] == '\'')
				make_inside_char_single(i, count, line_temp, ret);
			if (check_close == 0)
				check_close = 1;
			else if (check_close == 1)
				check_close = 0;
		}
		if (line_temp[*i] != '\"' || check_close == 0)
		{
			ret[*count] = line_temp[*i];
			ret[(*count) + 1] = 0;
			(*i)++;
			(*count)++;
		}
		else if (line_temp[*i] == '\"' && check_close == 1)
		{
			(*i)++;
			ret[*count] = line_temp[*i];
			ret[(*count) + 1] = 0;
			(*count)++;
			(*i)++;
			check_close = 0;
		}
		else
		{
			(*i)++;
			temp = (*i);
			return ;
		}
	}
	/*
	int	temp;

	(*i)++;
	while (line_temp && line_temp[*i])
	{
		if (line_temp[*i + 1] != ' ' && line_temp[*i] == '\"')
		{
			(*i)++;
			if (line_temp[*i] == '\'')
				make_inside_char_single(i, count, line_temp, ret);
		}
		else if (line_temp[*i] != '\"')
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
	*/
}

void	make_inside_char_single(int *i, int *count, char *line_temp, char *ret)
{
	int	temp;
	int	check_close;

	(*i)++;
	check_close = 0;
	while (line_temp && line_temp[*i])
	{
		if (line_temp[*i + 1] != ' ' && line_temp[*i] == '\'')
		{
			(*i)++;
			if (line_temp[*i] == '\"')
				make_inside_char_double(i, count, line_temp, ret);
			if (check_close == 0)
				check_close = 1;
			else if (check_close == 1)
				check_close = 0;
		}
		if (line_temp[*i] != '\'' || check_close == 0)
		{
			ret[*count] = line_temp[*i];
			ret[(*count) + 1] = 0;
			(*i)++;
			(*count)++;
		}
		else if (line_temp[*i] == '\'' && check_close == 1)
		{
			(*i)++;
			ret[*count] = line_temp[*i];
			ret[(*count) + 1] = 0;
			(*count)++;
			(*i)++;
			check_close = 0;
		}
		else
		{
			(*i)++;
			temp = (*i);
			return ;
		}
	}
}
