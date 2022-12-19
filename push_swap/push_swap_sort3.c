/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_sort3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 15:29:42 by gyopark           #+#    #+#             */
/*   Updated: 2022/12/19 23:01:50 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdio.h>

void	push_min_b(t_deque *a, t_deque *b, int min)
{
	int		head1;

	if (a->head == a->capacity - 1)
		head1 = 0;
	else
		head1 = a->head + 1;
	if (min < b->size / 2)
		while (min--)
			do_rb(b);
	else
	{
		while (b->size - min)
		{
			do_rrb(b);
			min++;
		}
	}
	do_pa(a, b);
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
