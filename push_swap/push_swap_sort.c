/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_sort.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 21:57:25 by gyopark           #+#    #+#             */
/*   Updated: 2022/12/21 17:38:36 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdio.h>

int	is_sorted(int *arr, int size)
{
	int		i;
	int		j;

	i = 0;
	while (i < size - 1)
	{
		j = i + 1;
		while (j < size)
		{
			if (arr[i] > arr[j])
				return (size);
			j++;
		}
		i++;
	}
	return (1);
}

int	sort_arr(t_deque *deq)
{
	int	*tmp_arr;
	int	idx;
	int	i;
	int	arg;

	tmp_arr = (int *)malloc(sizeof(int) * deq->size);
	idx = 0;
	i = deq->head - 1;
	if (deq->head < deq->tail)
		while (++i < deq->tail)
			tmp_arr[idx++] = deq->arr[i];
	else
	{
		while (++i < deq->capacity)
			tmp_arr[idx++] = deq->arr[i];
		i = -1;
		while (++i < deq->tail)
			tmp_arr[idx++] = deq->arr[i];
	}
	arg = is_sorted(tmp_arr, deq->size);
	free(tmp_arr);
	return (arg);
}

int	start_sort(t_deque *deq_a, t_deque *deq_b, t_deque *deq_str)
{
	int	arg;
	int	idx1;
	int	idx2;

	idx1 = deq_a->head;
	idx2 = deq_a->tail - 1;
	if (deq_a->arr[idx1] == deq_a->arr[idx2])
		return (0);
	arg = sort_arr(deq_a);
	if (arg == 1)
		return (0);
	else if (arg == 2)
		do_sa(deq_a);
	else if (arg == 3)
		sort_3(deq_a);
	else if (arg == 4)
		sort_4(deq_a, deq_b);
	else if (arg == 5)
		sort_5(deq_a, deq_b);
	else
		atob(deq_a, deq_b);
	deq_str = 0;
	return (0);
}
