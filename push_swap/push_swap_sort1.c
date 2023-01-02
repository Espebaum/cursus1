/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_sort1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 21:57:25 by gyopark           #+#    #+#             */
/*   Updated: 2023/01/01 20:26:20 by gyopark          ###   ########.fr       */
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

void	pi_push(t_deque *a, t_deque *b, int *pivot)
{
	int		large;

	large = a->size - (a->size / 3 * 2);
	while (a->size > large)
	{
		if (front(a) <= pivot[1])
		{
			do_pb(a, b);
			if (b->size > 1 && front(b) <= pivot[0])
				do_rb(b);
		}
		else
			do_ra(a);
	}
	while (a->size > 0)
		do_pb(a, b);
	free(pivot);
}

void	push_min_b(t_deque *a, t_deque *b)
{
	int	cnt;
	int	temp;
	int	min_idx;

	min_idx = get_min_idx(a, b);
	temp = same_cnt(a, b, min_idx);
	if (temp != 0)
	{
		merge_rr(a, b, min_idx, temp);
		return ;
	}
	cnt = b->size - min_idx + 1;
	if (min_idx++ < b->size / 2)
		while (--min_idx)
			do_rb(b);
	else
		while (--cnt)
			do_rrb(b);
	push_a(a, b, 0);
}

void	atob(t_deque *a, t_deque *b)
{	
	int		*pivot;
	int		*arr;
	int		sort_cnt;

	pivot = (int *)malloc(sizeof(int) * 2);
	arr = (int *) malloc(sizeof(int) * (a->size));
	get_pivot(a, pivot, arr);
	pi_push(a, b, pivot);
	sort_cnt = b->size;
	while (sort_cnt--)
		push_min_b(a, b);
	turn_min(a);
}

int	start_sort(t_deque *a, t_deque *b)
{
	int	arg;

	arg = is_sorted_arr(a, a->size);
	if (arg == 2)
		do_sa(a);
	else if (arg == 3)
		sort_3(a);
	else if (arg == 4)
		sort_4(a, b);
	else if (arg == 5)
		sort_5(a, b);
	else if (arg > 5)
		atob(a, b);
	return (0);
}
