/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_y2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark < gyopark@student.42seoul.kr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 19:22:14 by youngski          #+#    #+#             */
/*   Updated: 2023/02/14 21:43:44 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void	init_pure_word(int *sm_flag, int *du_flag)
{
	*sm_flag = 0;
	*du_flag = 0;
}

void	make_pure_word(int *i, int *count, char *line_temp, char *ret)
{
	int	sm_flag;
	int	du_flag;

	init_pure_word(&sm_flag, &du_flag);
	while (line_temp && line_temp[*i])
	{
		if (line_temp[*i] == '\'')
		{
			copy_bef_smlimiter(i, count, line_temp, ret);
			continue ;
		}
		if (line_temp[*i] == '\"')
		{
			copy_bef_lglimiter(i, count, line_temp, ret);
			continue ;
		}
		if (line_temp[*i] != ' ')
		{
			ret[*count] = line_temp[(*i)++];
			ret[(*count) + 1] = 0;
			(*count)++;
		}
		else
			return ;
	}
}
