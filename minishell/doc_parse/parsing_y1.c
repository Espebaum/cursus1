/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_y1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark < gyopark@student.42seoul.kr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 19:15:04 by youngski          #+#    #+#             */
/*   Updated: 2023/02/18 18:13:40 by youngski         ###   ########.fr       */
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
		if (line[i] == ' ' || line[i] == '<' || line[i] == '>'
			|| line[i] == '|')
		{
			if (line[i + 1] == '<' || line[i + 1] == '>')
				i++;
			cnt++;
			i++;
		}
		while (line[i] == ' ')
		{
			i++;
			cnt++;
		}
	}
	return (cnt + 2);
}

void	init_inside_char(char my_char, char *t, int *flag, int *i)
{
	if (my_char == '\"')
		*t = '\'';
	else
		*t = '\"';
	*flag = 0;
	(*i)++;
}

void	inside_char_plus(int *i, int *count)
{
	(*i)++;
	(*count)++;
}

void	count_inside_char(int *i, int *count, char *line_temp, char my_char)
{
	int		flag;
	char	t;

	init_inside_char(my_char, &t, &flag, i);
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
			inside_char_plus(i, count);
		}
		if (line_temp[*i] != my_char)
			inside_char_plus(i, count);
		else
		{
			(*i)++;
			return ;
		}
	}
}

int	make_inside_char_double(char *line_temp, char *ret, int *j)
{
	int	check_close;
	int	count;

	while (ret && *ret)
		ret++;
	count = 0;
	line_temp++;
	check_close = 0;
	while (*line_temp && check_close == 0)
	{
		if (*line_temp == '\"')
		{
			check_close = 1;
			if (count == 0)
			{
				ret[0] = 0;
				(*j)++;
			}
			count += 2;
			line_temp++;
			return (count);
		}
		ret[count] = *line_temp;
		ret[count + 1] = 0;
		line_temp++;
		count++;
	}
	return (count);
}

int	make_inside_char_single(char *line_temp, char *ret, int *j)
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
			if (count == 0)
			{
				ret[0] = 0;
				(*j)++;
			}
			count += 2;
			return (count);
		}
		ret[count] = *line_temp;
		ret[count + 1] = 0;
		line_temp++;
		count++;
	}
	return (count);
}
