/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 21:48:45 by gyopark           #+#    #+#             */
/*   Updated: 2023/02/02 16:42:11 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	rule_error(int *type_arr, int len)
{
	int		i;

	i = -1;
	while (i < len)
		if (type_arr[++i] == 6)
			return (-1);
	return (0);
}

int	get_cmds_num(int *type_arr, int token_len)
{
	int		i;
	int		cmds_num;

	i = -1;
	cmds_num = 0;
	while (++i < token_len)
		if (type_arr[i] == 2)
			cmds_num++;
	return (cmds_num);
}