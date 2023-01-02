/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_hard1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 15:51:25 by gyopark           #+#    #+#             */
/*   Updated: 2022/12/30 18:14:11 by gyopark          ###   ########.fr       */
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

int	sort_3(t_deque *a, t_deque *cmd)
{
	int	arr[3];

	deque_to_arr(a, arr);
	if (arr[0] > arr[1])
	{
		if (arr[0] > arr[2])
		{
			do_ra(a, cmd);
			if (arr[1] > arr[2])
				do_sa(a, cmd);
		}
		else
			do_sa(a, cmd);
	}
	else
	{
		if (arr[1] > arr[2])
		{
			do_rra(a, cmd);
			if (arr[2] > arr[0])
				do_sa(a, cmd);
		}
	}
	return (0);
}

int	sort_4(t_deque *a, t_deque *b, t_deque *cmd)
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
		do_ra(a, cmd);
	if (is_sorted_arr(a, a->size) == a->size)
	{
		do_pb(a, b, cmd);
		sort_3(a, cmd);
		do_pa(a, b, cmd);
	}
	return (0);
}

int	sort_5(t_deque *a, t_deque *b, t_deque *cmd)
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
			do_pb(a, b, cmd);
			i--;
		}
		else
			do_ra(a, cmd);
	}
	if (is_sorted_arr(a, a->size) == a->size)
		sort_3(a, cmd);
	if (front_idx(b, 0) < front_idx(b, 1))
		do_sb(b, cmd);
	do_pa(a, b, cmd);
	do_pa(a, b, cmd);
	return (0);
}
