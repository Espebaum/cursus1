/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_sort2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 15:35:34 by gyopark           #+#    #+#             */
/*   Updated: 2022/12/28 21:45:42 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdio.h>

void	pi_push(t_deque *a, t_deque *b, int *pivot)
{
	int		a_idx;

	a_idx = 0;
	while (a->size > 5)
	{
		if (front_idx(a, a_idx) < pivot[1])
		{
			do_pb(a, b);
			if (b->size > 1 && b->arr[b->head] < pivot[0])
				do_rb(b);
		}
		else
			do_ra(a);
		a_idx++;
	}
	sort_5(a, b);
	free(pivot);
	//체크
	/** int		idx = 0; */
	/** printf("파티셔닝된 b stack : "); */
	/** while (idx < b->size) */
	/**     printf("%d ", front_idx(b, idx++)); */
	/** printf("\n"); */
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
	int	a_case;
	int	b_cnt;
	int	a_cnt;
	int	max_acnt;
	int	same_cnt;

	max_acnt = a->size - get_min_a_idx(a);
	a_case = check_case(front_idx(b, min_idx), a);
	b_cnt = get_bcnt(b, min_idx);
	a_cnt = check_a_cnt(min_idx, a, b);
	if (min_idx < b->size / 2
		&& (a_cnt == get_min_a_idx(a) || a_cnt == check_a_up(a, b, min_idx)))
		same_cnt = ft_min(b_cnt, a_cnt);
	else if (min_idx >= b->size / 2
		&& (a_cnt == max_acnt || a_cnt == check_a_down(a, b, min_idx)))
			same_cnt = -ft_max(b_cnt, a_cnt);
	else
		same_cnt = 0;
	/** printf("b->size %d bcnt : %d acnt : %d same_cnt %d\n", b->size, b_cnt, a_cnt, same_cnt); */
	return (same_cnt);
}

void	check_cnt(t_deque *a, t_deque *b)
{
	int			b_cnt;
	int			idx;
	int			min_idx;
	int			temp;
	int			sum_cnt;

	sum_cnt = 2147483647;
	b_cnt = b->size;
	idx = -1;
	while (++idx < b->size)
	{
		temp = sum_cnt;
		b_cnt = get_bcnt(b, idx);
		/** printf("최초 bcnt : %d 최초 acnt : %d\n", b_cnt, check_a_cnt(idx, a, b)); */
		sum_cnt = ft_min(sum_cnt, b_cnt + check_a_cnt(idx, a, b));
		if (temp != sum_cnt)
			min_idx = idx;
		/** printf("min_idx : %d idx : %d\n", min_idx, idx); */
	}
	/** printf("중간 min_idx : %d\n", min_idx); */
	push_min_b(a, b, min_idx, temp);
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
	pi_push(a, b, pivot);
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
