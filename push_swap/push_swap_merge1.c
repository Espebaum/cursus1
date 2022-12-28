/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_merge1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 22:07:51 by gyopark           #+#    #+#             */
/*   Updated: 2022/12/28 19:45:15 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	rr_merge_ra(t_deque *a, t_deque *b, int min_idx, int temp)
{
	int	b_cnt;
	int	a_cnt;
	int	cnt;

	b_cnt = get_bcnt(b, min_idx);
	a_cnt = check_a_cnt(min_idx, a, b);
	cnt = a_cnt - b_cnt;
	while (temp--)
		do_rr(a, b);
	while (cnt--)
		do_ra(a);
	do_pa(a, b);
}

void	rr_merge_rb(t_deque *a, t_deque *b, int min_idx, int temp)
{
	int	b_cnt;
	int	a_cnt;
	int	cnt;

	b_cnt = get_bcnt(b, min_idx);
	a_cnt = check_a_cnt(min_idx, a, b);
	cnt = b_cnt - a_cnt;
	while (temp--)
		do_rr(a, b);
	while (cnt--)
		do_rb(b);
	do_pa(a, b);
}

void	rr_merge_rra(t_deque *a, t_deque *b, int min_idx, int temp)
{
	int	b_cnt;
	int	a_cnt;
	int	cnt;

	b_cnt = get_bcnt(b, min_idx);
	a_cnt = check_a_cnt(min_idx, a, b);
	cnt = a_cnt - b_cnt;
	while (temp--)
		do_rrr(a, b);
	while (cnt--)
		do_rra(a);
	do_pa(a, b);
}

void	rr_merge_rrb(t_deque *a, t_deque *b, int min_idx, int temp)
{
	int	b_cnt;
	int	a_cnt;
	int	cnt;

	b_cnt = get_bcnt(b, min_idx);
	a_cnt = check_a_cnt(min_idx, a, b);
	cnt = b_cnt - a_cnt;
	while (temp--)
		do_rrr(a, b);
	while (cnt--)
		do_rrb(b);
	do_pa(a, b);
}

#include <stdio.h>

void	merge_rr(t_deque *a, t_deque *b, int min_idx, int temp)
{
	int	b_cnt;
	int	a_cnt;

	b_cnt = get_bcnt(b, min_idx);
	a_cnt = check_a_cnt(min_idx, a, b);
	/** printf("a->size %d b->size %d min_idx %d bcnt : %d acnt : %d\n", a->size, b->size, min_idx, b_cnt, a_cnt); */
	if (temp == b_cnt)
		rr_merge_ra(a, b, min_idx, temp);
	else if (temp == a_cnt)
		rr_merge_rb(a, b, min_idx, temp);
	else if (temp == -b_cnt)
		rr_merge_rra(a, b, min_idx, -temp);
	else if (temp == -a_cnt)
		rr_merge_rrb(a, b, min_idx, -temp);
}
