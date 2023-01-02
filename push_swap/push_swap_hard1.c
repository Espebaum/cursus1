/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_hard1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 15:51:25 by gyopark           #+#    #+#             */
/*   Updated: 2023/01/01 20:31:54 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	front_idx(t_deque *deq, int idx)
{
	int	i;

	i = deq->head;
	i += idx;
	if (i >= deq->capacity)
		i -= deq->capacity;
	return (deq->arr[i]);
}

void	deque_to_arr(t_deque *d, int *a)
{
	int	i;

	i = -1;
	while (++i < d->size)
		a[i] = front_idx(d, i);
}

int	sort_3(t_deque *deq)
{
	int	a[3];

	deque_to_arr(deq, a);
	if (a[0] > a[1])
	{
		if (a[0] > a[2])
		{
			do_ra(deq);
			if (a[1] > a[2])
				do_sa(deq);
		}
		else
			do_sa(deq);
	}
	else
	{
		if (a[1] > a[2])
		{
			do_rra(deq);
			if (a[2] > a[0])
				do_sa(deq);
		}
	}
	return (0);
}

int	sort_4(t_deque *a, t_deque *b)
{
	int		i;
	int		arr[4];
	int		min_idx;

	deque_to_arr(a, arr);
	min_idx = 0;
	i = -1;
	while (++i < 4)
		if (arr[min_idx] > arr[i])
			min_idx = i;
	while (min_idx--)
		do_ra(a);
	if (is_sorted_arr(a, a->size) == a->size)
	{
		do_pb(a, b);
		sort_3(a);
		do_pa(a, b);
	}
	return (0);
}

int	sort_5(t_deque *a, t_deque *b)
{
	int		i;
	int		arr[5];

	if (is_sorted_arr(a, a->size) == 1)
		return (0);
	deque_to_arr(a, arr);
	my_qsort(arr, 0, 4);
	i = 2;
	while (i)
	{
		if (front_idx(a, 0) < arr[2])
		{
			do_pb(a, b);
			i--;
		}
		else
			do_ra(a);
	}
	if (is_sorted_arr(a, a->size) == a->size)
		sort_3(a);
	if (front_idx(b, 0) < front_idx(b, 1))
		do_sb(b);
	do_pa(a, b);
	do_pa(a, b);
	return (0);
}
