/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_exit2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark < gyopark@student.42seoul.kr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 20:12:05 by gyopark           #+#    #+#             */
/*   Updated: 2023/02/14 20:14:15 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exit_num_arg_req(char *str)
{
	printf("exit: ");
	printf("%s: ", str);
	printf("numeric argument required\n");
	exit(255);
	return (0);
}

int	is_exit_code_num(char *str)
{
	if (*str == '-')
		str++;
	if (*str == '\0')
		return (0);
	while (*str)
	{
		if (ft_isdigit(*str) == 0)
			return (0);
		str++;
	}
	return (1);
}

int	non_exit_many_arg(void)
{
	printf("exit: too many arguments\n");
	g_exit_code = 1;
	return (1);
}
