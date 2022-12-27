/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_sort2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 15:35:34 by gyopark           #+#    #+#             */
/*   Updated: 2022/12/27 16:05:41 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdio.h>

void	pi_push(t_deque *a, t_deque *b, int pivot1, int pivot2)
{
	int		a_idx;

	a_idx = 0;
	while (a->size > 5)
	{
		if (front_idx(a, a_idx) < pivot2)
		{
			do_pb(a, b);
			if (b->size > 1 && b->arr[b->head] < pivot1)
				do_rb(b);
		}
		else
			do_ra(a);
		a_idx++;
	}
	sort_5(a, b);
	//체크
	/** int		idx = 0; */
	/** b_size = b->size; */
	/** printf("파티셔닝된 b stack : "); */
	/** while (b_size--) */
	/**     printf("%d ", front_idx(b, idx++)); */
	/** printf("\n"); */
}

int	check_a_cnt(int idx, t_deque *a, t_deque *b)
{
	int		a_cnt;
	int		a_case;

	a_case = check_case(front_idx(b, idx), a);
	if (a_case == 1)
		a_cnt = 0;
	else if (a_case == 2)
		a_cnt = ft_min(check_a_up(a, b, idx), check_a_down(a, b, idx));
	else
		a_cnt = 1;
	return (a_cnt);
}

void	check_cnt(t_deque *a, t_deque *b)
{
	int			b_cnt;
	int			idx;
	int			min_idx;
	int			sum_check;
	int			sum_cnt;

	sum_cnt = 2147483647;
	b_cnt = b->size;
	idx = 0;
	while (idx < b->size)
	{
		sum_check = sum_cnt;
		b_cnt = ft_min(idx, ft_min(idx, (b->size) - idx));
		sum_cnt = ft_min(sum_cnt, b_cnt + check_a_cnt(idx, a, b));
		/** sum_cnt -= same_cnt(idx, check_a_cnt(idx, a, b)) */
		if (sum_check > sum_cnt)
			min_idx = idx;
		idx++;
	}
	push_min_b(a, b, min_idx);
	//체크
	/** int		a_size = a->size; */
	/** int		b_size = b->size; */
	/** idx = 0; */
	/** printf("\nb stack : "); */
	/** while (b_size--) */
	/**     printf("%d ", front_idx(b, idx++)); */
	/** printf("\na stack : "); */
	/** idx = 0; */
	/** while (a_size--) */
	/**     printf("%d ", front_idx(a, idx++)); */
	/** printf("\n"); */
}

void	atob(t_deque *a, t_deque *b)
{	
	int		*pivot;
	int		b_size;

	pivot = (int *)malloc(sizeof(int) * 2);
	get_pivot(a, pivot);
	pi_push(a, b, pivot[0], pivot[1]);
	b_size = b->size;
	while (b_size--)
		check_cnt(a, b);
	turn_min(a);
	//check
	/** int		a_size; */
	/** int		idx; */
	/** idx = 0; */
	/** a_size = a->size; */
	/** printf("최종 a stack : "); */
	/** while (a_size--) */
	/** { */
	/**     printf("%d ", front_idx(a, idx)); */
	/**     idx++; */
	/** } */
	/** printf("\n"); */
}
