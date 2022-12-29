/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 21:56:49 by gyopark           #+#    #+#             */
/*   Updated: 2022/12/29 20:24:10 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

const long long	g_long = 3000000000;
void	ft_freeall(char **spl);

long long	check_num(char *str)
{
	long long	ret;
	long long	sign;

	if (*str == '-')
		sign = -1;
	else if (isdigit(*str))
		sign = 1;
	else
		return (g_long);
	if (*str != '-')
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
	long long	l;

	spl = ft_split(s, ' ');
	save = spl;
	--spl;
	while (*(++spl))
	{
		l = check_num(*spl);
		arr[*idx] = l;
		(*idx)++;
	}
	ft_freeall(save);
}

void	split_space(char *s, int *num, t_deque *a)
{
	char		**spl;
	char		**save;
	long long	ret;
	int			len;

	len = ft_strlen(s);
	if (!is_bad_input(s) || *s == '\0')
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
	int	num;
	int	i;
	int	*arr;
	int	idx;

	i = 0;
	num = 0;
	if (argc == 1)
		return (error_exit(a));
	while (++i < argc)
		split_space(argv[i], &num, a);
	i = 0;
	idx = 0;
	arr = (int *) malloc(sizeof(int) * num);
	while (++i < argc)
		append_num(argv[i], arr, &idx);
	dup_check(arr, num, a);
	i = 0;
	push_arr_deq(arr, num, a);
	free(arr);
	return (0);
}

int	main(int argc, char **argv)
{
	t_deque		*a;
	t_deque		*b;

	a = make_deque();
	check_push_argv(argc, argv, a);
	b = make_deque();
	start_sort(a, b);
	delete_deque(a);
	delete_deque(b);
	/** system("leaks push_swap"); */
	return (0);
}
