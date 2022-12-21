/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_sort2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 15:35:34 by gyopark           #+#    #+#             */
/*   Updated: 2022/12/21 17:11:40 by gyopark          ###   ########.fr       */
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
	int		a_case;

	a_case = check_case(front_idx(b, idx), a);
	printf("최종 a_case : %d\n", a_case);
	if (a_case == 1)
		a_cnt = 0;
	else if (a_case == 2)
		a_cnt = ft_min(check_a_up(a, b, idx), check_a_down(a, b, idx));
	else
		a_cnt = 1;
	return (a_cnt);
}

void	first_check_cnt(t_deque *a, t_deque *b)
{
	do_pa(a, b);
	printf("\n");
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
		printf("idx : %d b cnt : %d a_cnt : %d\n", idx, b_cnt, check_a_cnt(idx, a, b));
		sum_cnt = ft_min(sum_cnt, b_cnt + check_a_cnt(idx, a, b));
		if (sum_check != sum_cnt)
			min_idx = idx;
		b_cnt++;
		if (b_cnt > b->size / 2)
			b_cnt = (b->size) - idx;
		idx++;
	}
	printf("최종 min idx : %d\n", min_idx);
	push_min_b(a, b, min_idx);
	/** push_min_a(a, b, min_idx); */
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
	printf("\n최종 a stack : ");
	i = 0;
	while (a_size--)
	{
		printf("%d ", front_idx(a, i++));
	}
}
