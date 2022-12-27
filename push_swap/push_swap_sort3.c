/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_sort3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 15:29:42 by gyopark           #+#    #+#             */
/*   Updated: 2022/12/27 14:41:49 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdio.h>

int	check_a_up(t_deque *a, t_deque *b, int idx)
{
	int	a_size;
	int	a_cnt;
	int	a_idx;
	int	a_pidx;

	a_idx = 0;
	a_pidx = a->size - 1;
	a_cnt = 0;
	a_size = a->size;
	while (a_size--)
	{
		if (front_idx(a, a_idx) < front_idx(b, idx)
			|| (front_idx(a, a_idx) > front_idx(b, idx)
				&& (front_idx(a, a_pidx) > front_idx(b, idx))))
		{
			a_cnt++;
			a_idx++;
			a_pidx = a_idx - 1;
		}
	}
	return (a_cnt);
}

int	check_a_down(t_deque *a, t_deque *b, int idx)
{
	int	a_size;
	int	a_cnt;
	int	a_idx;
	int	a_nidx;

	a_idx = a->size - 1;
	a_nidx = 0;
	a_cnt = 0;
	a_size = a->size;
	while (a_size--)
	{
		if (front_idx(a, a_idx) > front_idx(b, idx)
			|| (front_idx(a, a_idx) < front_idx(b, idx)
				&& front_idx(a, a_nidx) < front_idx(b, idx)))
		{
			a_cnt++;
			a_idx--;
			a_nidx = a_idx + 1;
		}
	}
	return (a_cnt);
}

void	push_a(t_deque *a, t_deque *b, int min_idx)
{
	int		a_case;

	a_case = check_case(front_idx(b, min_idx), a);
	/** printf("\na case : %d\n", a_case); */
	if (a->size == 1)
	{
		if (a->arr[a->head] < b->arr[b->head])
		{
			do_pa(a, b);
			do_sa(a);
		}
		else
			do_pa(a, b);
		return ;
	}
	if (a_case == 3)
		push_max_a(a, b);
	else if (a_case == 1)
		push_min_a(a, b);
	else
		push_mid_a(a, b, min_idx);
}

void	push_min_b(t_deque *a, t_deque *b, int min_idx)
{
	int		min;

	min = min_idx;
	if (min_idx < b->size / 2)
		while (min)
		{
			do_rb(b);
			min--;
		}
	else
		while (min)
		{
			do_rrb(b);
			min--;
		}
	//check
	/** printf("\nmin_idx : %d min : %d\n", min_idx, min); */
	/** printf("\n최저 b cnt인 b stack top : %d\n", b->arr[b->head]); */
	//
	push_a(a, b, min);
}
