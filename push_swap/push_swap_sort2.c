/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_sort2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 15:35:34 by gyopark           #+#    #+#             */
/*   Updated: 2022/12/30 14:33:56 by gyopark          ###   ########.fr       */
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
	int	same_cnt;
	int	a_cnt;
	int	a_case;
	int	a_flag;
	int	b_flag;

	a_case = check_case(front_idx(b, min_idx), a);
	same_cnt = 0;
	a_flag = 0;
	b_flag = 0;
	a_cnt = check_a_cnt(min_idx, a, b);
	if ((a_case == 1 || a_case == 3) && (a_cnt == a->size - get_min_a_idx(a)))
		a_flag = 1;
	if ((a_case == 2 && a_cnt == check_a_down(a, b, min_idx)))
		a_flag = 1;
	if (min_idx >= b->size / 2)
		b_flag = 1;
	if (a_flag == 0 && b_flag == 0)
		same_cnt = ft_min(min_idx, a_cnt);
	else if (a_flag == 1 && b_flag == 1)
		same_cnt = ft_max(-(b->size - min_idx), -a_cnt);
	else
		same_cnt = 0;
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
	min_idx = get_min_idx(a, b);
	temp = same_cnt(a, b, min_idx);
	push_min_b(a, b, temp);
}

void	atob(t_deque *a, t_deque *b)
{	
	int		pivot1;
	int		pivot2;
	int		*arr;
	int		sort_cnt;

	arr = (int *) malloc(sizeof(int) * (a->size));
	deque_to_arr(a, arr);
	my_qsort(arr, 0, a->size - 1);
	pivot1 = arr[a->size / 3];
	pivot2 = arr[a->size / 3 * 2];
	pi_push(a, b, pivot1, pivot2);
	free(arr);
	sort_cnt = b->size;
	while (sort_cnt--)
		check_cnt(a, b);
	turn_min(a);
}
