/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 21:48:45 by gyopark           #+#    #+#             */
/*   Updated: 2023/02/03 22:14:23 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	syntax_err(void)
{
	ft_putendl_fd("syntax error", 2);
	return (-1);
}

int	rule_error(int *type_arr, int len)
{
	int		i;

	i = -1;
	while (i < len)
		if (type_arr[++i] == T_ERROR)
			return (-1);
	return (0);
}

int	get_cmds_num(int *type_arr, int token_len)
{
	int		i;
	int		cmds_num;

	i = -1;
	cmds_num = 1;
	while (++i < token_len)
		if (type_arr[i] == T_PIPE)
			cmds_num++;
	return (cmds_num);
}