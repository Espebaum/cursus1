/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 21:56:49 by gyopark           #+#    #+#             */
/*   Updated: 2023/01/01 17:18:02 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

long long	check_num(char *str, long long err)
{
	long long	ret;
	long long	sign;

	if (ft_strlen(str) > 11)
		return (err);
	if (*str == '-')
		sign = -1;
	else if (*str == '+' || isdigit(*str))
		sign = 1;
	else
		return (err);
	if (*str != '-' && *str != '+')
		--str;
	ret = 0;
	while (*(++str))
	{
		if (!isdigit(*str))
			return (err);
		ret *= 10;
		ret += *str - '0';
	}
	if ((sign < 0 && ret <= 2147483648) || (sign > 0 && ret <= 2147483647))
		return (sign * ret);
	else
		return (err);
}

void	append_num(char *s, int *arr, int *idx, long long err)
{
	char		**spl;
	char		**save;
	long long	ret;

	spl = ft_split(s, ' ');
	save = spl;
	--spl;
	while (*(++spl))
	{
		ret = check_num(*spl, err);
		arr[*idx] = ret;
		(*idx)++;
	}
	ft_freeall(save);
}

void	count_num(char *s, int *num, t_deque *a, long long err)
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
		ret = check_num(*spl, err);
		if (ret == err || ((*spl)[0] == '-' && (*spl)[1] == '\0')
			|| ((*spl)[0] == '+' && (*spl)[1] == '\0'))
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
	int				num;
	int				len;
	int				*arr;
	int				idx;
	long long		err;

	len = 0;
	num = 0;
	err = 3000000000;
	while (++len < argc)
		count_num(argv[len], &num, a, err);
	len = 0;
	idx = 0;
	arr = (int *) malloc(sizeof(int) * num);
	while (++len < argc)
		append_num(argv[len], arr, &idx, err);
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

	if (argc == 1)
		return (0);
	cmd = make_deque();
	a = make_deque();
	check_push_argv(argc, argv, a);
	b = make_deque();
	start_sort(a, b, cmd);
	print_cmd(cmd);
	delete_deque(a);
	delete_deque(b);
	delete_deque(cmd);
	return (0);
}
