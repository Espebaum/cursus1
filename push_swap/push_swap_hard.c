/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_hard.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 15:51:25 by gyopark           #+#    #+#             */
/*   Updated: 2022/12/18 15:00:46 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	front_idx(t_deque *deq, int idx)
{
	int	i;

	i = deq->head;
	while (idx--)
	{
		i++;
		if (i == deq->capacity)
			i = 0;
	}
	return (deq->arr[i]);
}

void	deque_to_arr(t_deque *d, int *a)
{
	int	i;

	i = -1;
	while (++i < d->size)
		a[i] = front_idx(d, i);
}

int	is_sorted_deq(t_deque *a)
{
	int		i;
	int		cur;
	int		val;

	cur = a->head;
	val = a->arr[cur];
	i = a->size;
	if (!i)
		return (1);
	while (--i)
	{
		cur++;
		if (cur == a->capacity)
			cur = 0;
		if (val > a->arr[cur])
			return (0);
		val = a->arr[cur];
	}
	return (1);
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
	if (!is_sorted_deq(a))
	{
		do_pb(a, b);
		sort_3(a);
		do_pa(a, b);
	}
	return (0);
}
