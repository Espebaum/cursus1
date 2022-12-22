/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_sort3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 15:29:42 by gyopark           #+#    #+#             */
/*   Updated: 2022/12/22 18:35:46 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	check_a_up(t_deque *a, t_deque *b, int idx)
{
	int	a_size;
	int	a_head;
	int	a_cnt;

	a_cnt = 0;
	a_head = a->head;
	a_size = a->size;
	while (a_size--)
	{
		if (a->arr[a_head] < front_idx(b, idx))
		{
			a_cnt++;
			a_head++;
			if (a_head == a->capacity)
				a_head = 0;
		}
	}
	return (a_cnt);
}

int	check_a_down(t_deque *a, t_deque *b, int idx)
{
	int	a_size;
	int	a_head;
	int	a_tail;
	int	a_cnt;

	a_cnt = 0;
	a_head = a->head;
	a_tail = a->tail - 1;
	a_size = a->size;
	while (a_size--)
	{
		if (a->arr[a_tail] > front_idx(b, idx)
			|| (a->arr[a_tail] < front_idx(b, idx)
				&& a->arr[a_head] < front_idx(b, idx)))
		{
			a_cnt++;
			a_tail--;
			if (a_tail < 0)
				a_tail = a->capacity;
		}
	}
	return (a_cnt);
}

void	push_a(t_deque *a, t_deque *b, int min_idx)
{
	int		a_case;

	a_case = check_case(front_idx(b, min_idx), a);
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
		while (min--)
			do_rb(b);
	else
		while (min--)
			do_rrb(b);
	push_a(a, b, min_idx);
}
