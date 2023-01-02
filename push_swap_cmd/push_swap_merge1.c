/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_merge1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 22:07:51 by gyopark           #+#    #+#             */
/*   Updated: 2022/12/30 21:42:28 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	rr_merge_ra(t_deque *a, t_deque *b, t_deque *cmd, int temp)
{
	int	b_cnt;
	int	a_cnt;
	int	cnt;
	int	min_idx;

	min_idx = get_min_idx(a, b);
	b_cnt = min_idx;
	a_cnt = check_a_cnt(min_idx, a, b);
	cnt = a_cnt - b_cnt + 1;
	while (temp--)
		do_rr(a, b, cmd);
	while (--cnt)
		do_ra(a, cmd);
	do_pa(a, b, cmd);
}

void	rr_merge_rb(t_deque *a, t_deque *b, t_deque *cmd, int temp)
{
	int	b_cnt;
	int	a_cnt;
	int	cnt;
	int	min_idx;

	min_idx = get_min_idx(a, b);
	b_cnt = min_idx;
	a_cnt = check_a_cnt(min_idx, a, b);
	cnt = b_cnt - a_cnt + 1;
	while (temp--)
		do_rr(a, b, cmd);
	while (--cnt)
		do_rb(b, cmd);
	do_pa(a, b, cmd);
}

void	rr_merge_rra(t_deque *a, t_deque *b, t_deque *cmd, int temp)
{
	int	b_cnt;
	int	a_cnt;
	int	cnt;
	int	min_idx;

	min_idx = get_min_idx(a, b);
	b_cnt = b->size - min_idx;
	a_cnt = check_a_cnt(min_idx, a, b);
	cnt = a_cnt - b_cnt + 1;
	while (temp--)
		do_rrr(a, b, cmd);
	while (--cnt)
		do_rra(a, cmd);
	do_pa(a, b, cmd);
}

void	rr_merge_rrb(t_deque *a, t_deque *b, t_deque *cmd, int temp)
{
	int	b_cnt;
	int	a_cnt;
	int	cnt;
	int	min_idx;

	min_idx = get_min_idx(a, b);
	b_cnt = b->size - min_idx;
	a_cnt = check_a_cnt(min_idx, a, b);
	cnt = b_cnt - a_cnt + 1;
	while (temp--)
		do_rrr(a, b, cmd);
	while (--cnt)
		do_rrb(b, cmd);
	do_pa(a, b, cmd);
}

void	merge_rr(t_deque *a, t_deque *b, t_deque *cmd, int temp)
{
	int	b_cnt;
	int	a_cnt;
	int	min_idx;

	min_idx = get_min_idx(a, b);
	b_cnt = min_idx;
	a_cnt = check_a_cnt(min_idx, a, b);
	if (temp == b_cnt)
		rr_merge_ra(a, b, cmd, temp);
	else if (temp == a_cnt)
		rr_merge_rb(a, b, cmd, temp);
	else if (temp == -(b->size - min_idx))
		rr_merge_rra(a, b, cmd, -temp);
	else if (temp == -a_cnt)
		rr_merge_rrb(a, b, cmd, -temp);
}
