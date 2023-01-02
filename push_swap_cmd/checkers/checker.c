/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 21:56:49 by gyopark           #+#    #+#             */
/*   Updated: 2022/12/31 17:30:05 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"
#include <stdio.h>

const long long	g_long = 3000000000;

long long	check_num(char *str)
{
	long long	ret;
	long long	sign;

	if (*str == '-')
		sign = -1;
	else if (*str == '+' || isdigit(*str))
		sign = 1;
	else
		return (g_long);
	if (*str != '-' && *str != '+')
		--str;
	ret = 0;
	while (*(++str))
	{
		if (!isdigit(*str))
			return (g_long);
		ret *= 10;
		ret += *str - '0';
	}
	if ((sign < 0 && ret <= 2147483648)
		|| (sign > 0 && ret <= 2147483647))
		return (sign * ret);
	else
		return (g_long);
}

void	append_num(char *s, int *arr, int *idx)
{
	char		**spl;
	char		**save;
	long long	ret;

	spl = ft_split(s, ' ');
	save = spl;
	--spl;
	while (*(++spl))
	{
		ret = check_num(*spl);
		arr[*idx] = ret;
		(*idx)++;
	}
	ft_freeall(save);
}

void	count_num(char *s, int *num, t_deque *a)
{
	char		**spl;
	char		**save;
	long long	ret;

	if (is_bad_input(s))
		error_exit(a);
	spl = ft_split(s, ' ');
	save = spl;
	if (!spl)
		error_exit(a);
	--spl;
	while (*(++spl))
	{
		ret = check_num(*spl);
		if (ret == g_long || ((*spl)[0] == '-' && (*spl)[1] == '\0'))
		{
			ft_freeall(save);
			error_exit(a);
		}
		(*num)++;
	}
	ft_freeall(save);
}

int	check_push_argv(int argc, char **argv, t_deque *a)
{
	int		num;
	int		len;
	int		*arr;
	int		idx;

	len = 0;
	num = 0;
	while (++len < argc)
		count_num(argv[len], &num, a);
	len = 0;
	idx = 0;
	arr = (int *) malloc(sizeof(int) * num);
	while (++len < argc)
		append_num(argv[len], arr, &idx);
	dup_check(arr, num, a);
	len = 0;
	while (len < num)
		push_back(a, arr[len++]);
	free(arr);
	return (0);
}

int	main(int argc, char **argv)
{
	t_deque		*a;
	t_deque		*b;
	t_deque		*cmd;
	char		*line;

	if (argc == 1)
		return (0);
	cmd = make_deque();
	a = make_deque();
	check_push_argv(argc, argv, a);
	b = make_deque();
	while (1)
	{
		line = get_next_line(0);
		if (!line)
			break ;
		check_cmd(line, a, b, cmd);
		free(line);
	}
	check_condition(a, b);
	delete_deque(a);
	delete_deque(b);
	delete_deque(cmd);
	return (0);
}
