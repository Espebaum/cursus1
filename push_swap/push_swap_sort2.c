/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_sort2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 15:35:34 by gyopark           #+#    #+#             */
/*   Updated: 2022/12/20 22:34:24 by gyopark          ###   ########.fr       */
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
	printf("\n파티셔닝\n");
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

int	check_a_cnt(int idx, t_deque *a, t_deque *b)
{
	int		a_cnt;
	int		a_head;
	int		a_size;

	a_cnt = 0;
	a_head = a->head;
	a_size = a->size;
	a_cnt = ft_min(check_a_up(a, b, idx), check_a_down(a, b, idx));
	return (a_cnt);
}

void	first_check_cnt(t_deque *a, t_deque *b)
{
	do_pa(a, b);
	return ;
}

void	check_cnt(t_deque *a, t_deque *b)
{
	int			b_cnt;
	int			idx;
	int			min_idx;
	int			sum_check;
	int			sum_cnt;

	sum_cnt = b->size;
	b_cnt = b->size;
	idx = 0;
	while (idx < b->size)
	{
		sum_check = sum_cnt;
		b_cnt = ft_min(b_cnt, ft_min(idx, (b->size) - idx));
		sum_cnt = ft_min(sum_cnt, b_cnt + check_a_cnt(idx, a, b));
		if (sum_check != sum_cnt)
			min_idx = idx;
		idx++;
	}
	push_min_b(b, min_idx);
	push_min_a(a, b, min_idx);
}

void	atob(t_deque *a, t_deque *b)
{	
	int		*arr;
	int		pivot1;
	int		pivot2;
	int		b_size;
	int		a_size; // 체크
	int		i;		// 체크

	arr = (int *) malloc(sizeof(int) * a->size);
	deque_to_arr(a, arr);
	my_qsort(arr, 0, a->size);
	pivot1 = arr[a->size / 3];
	pivot2 = arr[(a->size / 3) * 2];
	printf("pivot1: %d pivot2: %d\n", pivot1, pivot2);
	pi_push(a, b, pivot1, pivot2);
	first_check_cnt(a, b);
	b_size = b->size;
	while (b_size--)
		check_cnt(a, b);
	//체크
	a_size = a->size;
	printf("a stack : ");
	i = 0;
	while (a_size--)
	{
		printf("%d ", front_idx(a, i++));
	}
}
