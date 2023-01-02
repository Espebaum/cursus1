/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_sort3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 15:29:42 by gyopark           #+#    #+#             */
/*   Updated: 2022/12/30 21:43:18 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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

void	push_min_a(t_deque *a, t_deque *b, t_deque *cmd, int min_a_idx)
{
	int		cnt;

	cnt = a->size - min_a_idx;
	if (min_a_idx > a->size / 2)
	{
		while (cnt--)
			do_rra(a, cmd);
	}
	else
	{
		while (min_a_idx--)
			do_ra(a, cmd);
	}
	do_pa(a, b, cmd);
}

void	push_mid_a(t_deque *a, t_deque *b, t_deque *cmd)
{
	int	up;
	int	down;

	up = check_a_up(a, b, 0);
	down = check_a_down(a, b, 0);
	if (ft_min(up, down) == up)
		while (up--)
			do_ra(a, cmd);
	else
		while (down--)
			do_rra(a, cmd);
	do_pa(a, b, cmd);
}

void	push_a(t_deque *a, t_deque *b, t_deque *cmd, int min_idx)
{
	int		min_a_idx;
	int		a_case;

	min_a_idx = get_min_a_idx(a);
	a_case = check_case(front_idx(b, min_idx), a);
	if (a_case == 1 || a_case == 3)
		push_min_a(a, b, cmd, min_a_idx);
	else
		push_mid_a(a, b, cmd);
}
