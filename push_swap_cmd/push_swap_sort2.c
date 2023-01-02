/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_sort2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 15:35:34 by gyopark           #+#    #+#             */
/*   Updated: 2022/12/30 20:02:23 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	get_bcnt(t_deque *b, int idx)
{
	int	b_cnt;
	int	cnt;

	cnt = b->size - idx;
	b_cnt = ft_min(idx, cnt);
	return (b_cnt);
}

int	check_a_cnt(int idx, t_deque *a, t_deque *b)
{
	int		a_cnt;
	int		a_case;
	int		min_a_idx;
	int		cnt;

	a_case = check_case(front_idx(b, idx), a);
	min_a_idx = get_min_a_idx(a);
	if (a_case == 1 || a_case == 3)
	{
		cnt = a->size - min_a_idx;
		a_cnt = ft_min(min_a_idx, cnt);
	}
	else
		a_cnt = ft_min(check_a_up(a, b, idx), check_a_down(a, b, idx));
	return (a_cnt);
}

int	same_cnt(t_deque *a, t_deque *b, int min_idx)
{
	int	same_cnt;
	int	a_cnt;
	int	a_case;
	int	a_flag;
	int	b_flag;

	a_case = check_case(front_idx(b, min_idx), a);
	same_cnt = 0;
	a_flag = 0;
	b_flag = 0;
	a_cnt = check_a_cnt(min_idx, a, b);
	if ((a_case == 1 || a_case == 3) && (a_cnt == a->size - get_min_a_idx(a)))
		a_flag = 1;
	if ((a_case == 2 && a_cnt == check_a_down(a, b, min_idx)))
		a_flag = 1;
	if (min_idx >= b->size / 2)
		b_flag = 1;
	if (a_flag == 0 && b_flag == 0)
		same_cnt = ft_min(min_idx, a_cnt);
	else if (a_flag == 1 && b_flag == 1)
		same_cnt = ft_max(-(b->size - min_idx), -a_cnt);
	else
		same_cnt = 0;
	return (same_cnt);
}

int	get_min_idx(t_deque *a, t_deque *b)
{
	int		idx;
	int		b_cnt;
	int		sum_cnt;
	int		min_idx;
	int		temp;

	b_cnt = b->size;
	sum_cnt = 2147483647;
	idx = -1;
	while (++idx < b->size)
	{
		temp = sum_cnt;
		b_cnt = get_bcnt(b, idx);
		sum_cnt = ft_min(sum_cnt, b_cnt + check_a_cnt(idx, a, b));
		if (temp != sum_cnt)
			min_idx = idx;
	}
	return (min_idx);
}
