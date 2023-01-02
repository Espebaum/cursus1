/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_sort1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 21:57:25 by gyopark           #+#    #+#             */
/*   Updated: 2022/12/30 22:41:06 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	is_sorted_arr(t_deque *a, int size)
{
	int		i;
	int		j;

	i = 0;
	while (i < size - 1)
	{
		j = i + 1;
		while (j < size)
		{
			if (front_idx(a, i) > front_idx(a, j))
				return (size);
			j++;
		}
		i++;
	}
	return (1);
}

void	pi_push(t_deque *a, t_deque *b, int *pivot, t_deque *cmd)
{
	int		large;

	large = a->size - (a->size / 3 * 2);
	while (a->size > large)
	{
		if (front(a) <= pivot[1])
		{
			do_pb(a, b, cmd);
			if (b->size > 1 && front(b) <= pivot[0])
				do_rb(b, cmd);
		}
		else
			do_ra(a, cmd);
	}
	while (a->size > 0)
		do_pb(a, b, cmd);
	free(pivot);
}

void	push_min_b(t_deque *a, t_deque *b, t_deque *cmd)
{
	int	cnt;
	int	temp;
	int	min_idx;

	min_idx = get_min_idx(a, b);
	temp = same_cnt(a, b, min_idx);
	if (temp != 0)
	{
		merge_rr(a, b, cmd, temp);
		return ;
	}
	cnt = b->size - min_idx + 1;
	if (min_idx++ < b->size / 2)
		while (--min_idx)
			do_rb(b, cmd);
	else
		while (--cnt)
			do_rrb(b, cmd);
	push_a(a, b, cmd, 0);
}

void	atob(t_deque *a, t_deque *b, t_deque *cmd)
{	
	int		*pivot;
	int		*arr;
	int		sort_cnt;

	pivot = (int *)malloc(sizeof(int) * 2);
	arr = (int *) malloc(sizeof(int) * (a->size));
	get_pivot(a, pivot, arr);
	pi_push(a, b, pivot, cmd);
	sort_cnt = b->size;
	while (sort_cnt--)
		push_min_b(a, b, cmd);
	turn_min(a, cmd);
}

int	start_sort(t_deque *a, t_deque *b, t_deque *cmd)
{
	int	arg;

	arg = is_sorted_arr(a, a->size);
	if (arg == 2)
		do_sa(a, cmd);
	else if (arg == 3)
		sort_3(a, cmd);
	else if (arg == 4)
		sort_4(a, b, cmd);
	else if (arg == 5)
		sort_5(a, b, cmd);
	else if (arg > 5)
		atob(a, b, cmd);
	return (0);
}
