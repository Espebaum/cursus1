/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_sort2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 15:35:34 by gyopark           #+#    #+#             */
/*   Updated: 2022/12/19 22:48:33 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdio.h>

void	pi_push(t_deque *a, t_deque *b, int pivot1, int pivot2)
{
	int		a_size;
	int		b_size;
	int		idx;

	a_size = a->size;
	b_size = b->size;
	while (a_size)
	{
		if (a->arr[a->head] <= pivot2)
		{
			do_pb(a, b);
			if (b->size > 1 && b->arr[b->head] <= pivot1)
				do_rb(b);
		}
		else
			do_ra(a);
		a_size--;
	}
	a_size = a->size;
	while (a_size)
	{
		do_pb(a, b);
		(a_size)--;
	}
	printf("\n파티셔닝 b스택\n"); 
	b_size = b->size;
	printf("b stack : ");
	idx = 0;
	while (b_size--)
	{
		printf("%d ", front_idx(b, idx));
		idx++;
	}
	printf("\n\n");
}

void	check_a_cnt(int *b_cnt, t_deque *a, t_deque *b)
{
	int		idx;
	int		b_size;
	int		a_head;
	int		a_size;
	int		min;

	b_size = b->size;
	idx = 0;
	while (b_size--)
	{
		a_size = a->size;
		a_head = a->head;
		while (a_size--)
		{
			if (a->arr[a_head] < front_idx(b, idx))
			{
				b_cnt[idx]++;
				a_head++;
			}
		}
		idx++;
	}
	min = check_min_idx(b_cnt, b->size);
	push_min_b(a, b, min);
}

void	check_b_cnt(t_deque *a, t_deque *b)
{
	int			*b_cnt;
	int			b_size;
	int			idx;
	static int	first = 0;

	idx = 0;
	b_size = b->size;
	if (first == 0)
	{
		do_pa(a, b);
		first++;
		return ;
	}
	b_cnt = (int *)malloc(sizeof(int) * b_size);
	while (b_size--)
	{
		if (idx > (b->size) / 2)
			b_cnt[idx] = (b->size) - idx;
		else
			b_cnt[idx] = idx;
		idx++;
	}
	check_a_cnt(b_cnt, a, b);
	free(b_cnt);
}

void	check_cnt_push(t_deque *a, t_deque *b)
{
	check_b_cnt(a, b);
}

void	atob(t_deque *a, t_deque *b)
{	
	int		*arr;
	int		pivot1;
	int		pivot2;
	int		b_size;

	b_size = b->size;
	arr = (int *) malloc(sizeof(int) * a->size);
	deque_to_arr(a, arr);
	my_qsort(arr, 0, a->size);
	pivot1 = arr[a->size / 3];
	pivot2 = arr[(a->size / 3) * 2];
	printf("pivot1: %d pivot2: %d\n", pivot1, pivot2);
	pi_push(a, b, pivot1, pivot2);
	check_cnt_push(a, b);
	b_size = b->size;
	while (b_size)
	{
		check_cnt_push(a, b);
		b_size--;
	}
}
