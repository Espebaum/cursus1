/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_sort3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 15:29:42 by gyopark           #+#    #+#             */
/*   Updated: 2022/12/20 16:54:41 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdio.h>

int	check_a_up(t_deque)
{

}

int	check_a_down()
{

}

int	check_min_idx(int *arr, int size)
{
	int	i;
	int	min_idx;

	i = 0;
	min_idx = 0;
	while (i < size)
	{
		if (arr[min_idx] > arr[i++])
			min_idx = i;
	}
	return (min_idx);
}

void	push_min_a(int *a_cnt, t_deque *a, t_deque *b, int min)
{
	while (a_cnt[min]--)
	{
		if (min < a->size / 2)
			do_ra(a);
		else
			do_rra(a);
		a_cnt[min]--;
	}
	do_pa(a, b);
	printf("a->head %d\n", a->arr[a->head]);
	printf("b->head %d\n", b->arr[b->head]);
}

void	push_min_b(t_deque *a, t_deque *b, int *a_cnt, int min)
{
	while (1)
	{
		if (b->arr[b->head] == front_idx(b, min))
			break ;
		if (min > b->size / 2)
			do_rrb(b);
		else
			do_rb(b);
	}
	if (a->size == 1)
	{
		if (b->arr[b->head] > a->arr[a->head])
		{
			do_pa(a, b);
			do_sa(a);
		}
		else
			do_pa(a, b);
		return ;
	}
	else
		push_min_a(a_cnt, a, b, min);
}
