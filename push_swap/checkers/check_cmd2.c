/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 16:38:48 by gyopark           #+#    #+#             */
/*   Updated: 2022/12/31 16:55:39 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

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

void	my_qsort(int *arr, int left, int right)
{
	int		l;
	int		r;
	int		mid;
	int		tmp;

	if (left >= right)
		return ;
	l = left - 1;
	r = right + 1;
	mid = arr[(l + r) / 2];
	while (1)
	{
		while (arr[++l] < mid)
			;
		while (arr[--r] > mid)
			;
		if (l >= r)
			break ;
		tmp = arr[l];
		arr[l] = arr[r];
		arr[r] = tmp;
	}
	my_qsort(arr, left, l - 1);
	my_qsort(arr, r + 1, right);
}
