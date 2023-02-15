/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_exit1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark < gyopark@student.42seoul.kr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 20:53:24 by gyopark           #+#    #+#             */
/*   Updated: 2023/02/15 21:31:00 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_long_min(char *str, int *idx, const char *mn)
{
	while (str[++(*idx)])
	{
		if (str[*idx] > mn[*idx])
			return (1);
		else if (str[*idx] < mn[*idx])
			return (0);
		if (*idx == 19 && str[*idx] > mn[*idx])
			return (1);
	}
	return (0);
}

int	is_long_max(char *str, int *idx, const char *mx)
{
	while (str[++(*idx)])
	{
		if (str[*idx] > mx[*idx])
			return (1);
		else if (str[*idx] < mx[*idx])
			return (0);
		if (*idx == 19 && str[*idx] > mx[*idx])
			return (1);
	}
	return (0);
}

int	is_long_min_max(char *str, int is_minus)
{
	const char	mx[19] = "9223372036854775807";
	const char	mn[19] = "9223372036854775808";
	int			idx;
	int			res;

	idx = -1;
	if (is_minus == 1)
	{
		res = is_long_min(str, &idx, mn);
		if (res == 1)
			return (1);
		else if (res == 0)
			return (0);
	}
	else
	{
		res = is_long_max(str, &idx, mx);
		if (res == 1)
			return (1);
		else if (res == 0)
			return (0);
	}
	return (0);
}

int	check_code_long(char *str)
{
	int	i;
	int	is_minus;
	int	ret;

	i = -1;
	is_minus = 0;
	ret = 0;
	if (*str == '-')
	{
		str++;
		is_minus = 1;
	}
	if (ft_strlen(str) == 19)
		ret = is_long_min_max(str, is_minus);
	else if (ft_strlen(str) > 19)
		ret = 1;
	return (ret);
}

int	call_exit(char **builtin)
{
	int	is_first_arg_num;
	int	exit_code;

	printf("exit\n");
	if (builtin[1] == NULL)
		exit(0);
	is_first_arg_num = is_exit_code_num(builtin[1]);
	if (is_first_arg_num == 0)
		exit_num_arg_req(builtin[1]);
	if (builtin[2] != NULL)
		return (non_exit_many_arg());
	if (check_code_long(builtin[1]) == 1)
		exit_num_arg_req(builtin[1]);
	exit_code = ft_atoi(builtin[1]);
	exit(exit_code);
	return (0);
}
