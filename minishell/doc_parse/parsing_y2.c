/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_y2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark < gyopark@student.42seoul.kr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 19:22:14 by youngski          #+#    #+#             */
/*   Updated: 2023/02/15 19:00:51 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_pure_word(int *sm_flag, int *du_flag)
{
	*sm_flag = 0;
	*du_flag = 0;
}

int	make_pure_word(char *line_temp, char *ret)
{
	int	sm_flag;
	int	du_flag;
	int	count;

	count = 0;
	init_pure_word(&sm_flag, &du_flag);
	while (ret && *ret)
		ret++;
	while (line_temp && *line_temp)
	{
		if (*line_temp == '<')
		{
			if (*line_temp == '<')
			{
				ret[count] = *line_temp;
				line_temp++;
				ret[(count) + 1] = 0;
				(count)++;
			}
			ret[count] = *line_temp;
			line_temp++;
			ret[(count) + 1] = 0;
			(count)++;
			return (count);
		}
		if (*line_temp && *line_temp != ' ' && *line_temp != '\''
			&& *line_temp != '\"')
		{
			ret[count] = *line_temp;
			line_temp++;
			ret[(count) + 1] = 0;
			(count)++;
		}
		else
			return (count);
	}
	return (count);
}
