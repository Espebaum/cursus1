/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 21:56:49 by gyopark           #+#    #+#             */
/*   Updated: 2022/12/18 15:07:20 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

const long long	g_max = 2147483647;
const long long	g_min = -2147483648;
const long long	g_ll = 3000000000;
void	ft_freeall(char **spl);

long long	check_num(char *str)
{
	long long	l;
	long long	neg;

	if (*str == '-')
		neg = -1;
	else if (*str >= '0' && *str <= '9')
		neg = 1;
	else
		return (g_ll);
	if (*str != '-')
		--str;
	l = 0;
	while (*(++str))
	{
		if (*str < '0' || *str > '9')
			return (g_ll);
		l *= 10LL;
		l += *str - '0';
	}
	if ((neg < 0 && l <= -g_min) || (neg > 0 && l <= g_max))
		return (neg * l);
	else
		return (g_ll);
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

void	split_space(char *s, int *num)
{
	char		**spl;
	char		**save;
	long long	l;
	int			i;

	i = ft_strlen(s);
	if (*s == ' ' && *(s + 1) == '\0')
		error_exit();
	spl = ft_split(s, ' ');
	save = spl;
	if (!spl)
		error_exit();
	--spl;
	while (*(++spl))
	{
		l = check_num(*spl);
		if (l == g_ll || ((*spl)[0] == '-' && (*spl)[1] == '\0'))
		{
			ft_freeall(save);
			error_exit();
		}
		(*num)++;
	}
	ft_freeall(save);
}

int	check_push_argv(int argc, char **argv, t_deque *deq)
{
	int	n;
	int	i;
	int	*arr;
	int	idx;

	i = 0;
	n = 0;
	if (argc == 1)
		return (error_exit());
	while (++i < argc)
		split_space(argv[i], &n);
	i = 0;
	idx = 0;
	arr = (int *) malloc(sizeof(int) * n);
	while (++i < argc)
		append_num(argv[i], arr, &idx);
	dup_check(arr, n);
	i = 0;
	push_arr_deq(arr, n, deq);
	free(arr);
	return (0);
}

int	main(int argc, char **argv)
{
	t_deque		*deq_a;
	t_deque		*deq_b;
	t_deque		*deq_str;
	int			i;

	i = 0;
	deq_a = make_deque();
	deq_b = make_deque();
	deq_str = make_deque();
	check_push_argv(argc, argv, deq_a);
	start_sort(deq_a, deq_b, deq_str);
	return (0);
}
