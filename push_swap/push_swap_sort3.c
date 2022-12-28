/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_sort3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 15:29:42 by gyopark           #+#    #+#             */
/*   Updated: 2022/12/28 21:45:31 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdio.h>

int	get_bcnt(t_deque *b, int idx)
{
	int	b_cnt;
	int	cnt;

	cnt = b->size - idx;
	b_cnt = ft_min(idx, cnt);
	return (b_cnt);
}

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
	if (a_case == 1 || a_case == 3)
		push_min_a(a, b);
	else
		push_mid_a(a, b, min_idx);
}

void	push_min_b(t_deque *a, t_deque *b, int min_idx, int temp)
{
	int	cnt;

	temp = 0;
	/** if (temp != 0) */
	/** { */
	/**     merge_rr(a, b, min_idx, temp); */
	/**     return ; */
	/** } */
    /**  */
	/** printf("min_idx : %d b->size : %d b->size 절반 : %d\n", min_idx, b->size, b->size / 2); */
	cnt = b->size - min_idx;
	if (min_idx < b->size / 2)
	{
		while (min_idx)
		{
			do_rb(b);
			min_idx--;
		}
	}
	else
	{
		while (cnt--)
			do_rrb(b);
	}
	//check
	/** printf("\nmin_idx : %d min : %d\n", min_idx, min); */
	/** printf("\n최저 b cnt인 b stack top : %d\n", b->arr[b->head]); */
	//
	push_a(a, b, 0);
}
