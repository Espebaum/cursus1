/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_deque1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:31:08 by gyopark           #+#    #+#             */
/*   Updated: 2022/12/14 18:36:12 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

const int	g_memory_border = 1024;

void	swap_top(t_deque *d)
{
	int		tmp;
	int		idx1;
	int		idx2;

	idx1 = d->head;
	if (idx1 == d->capacity - 1)
		idx2 = 0;
	else
		idx2 = idx1 + 1;
	tmp = d->arr[idx1];
	d->arr[idx1] = d->arr[idx2];
	d->arr[idx2] = tmp;
}

// 22 운 없이 헤드가 capacity - 1의 인덱스일 경우

// push_back, push_front 구현
// pop_back, pop_front 구현
// 위 함수들을 이용하여 rotate, reverse rotate 구현

void	push_back(t_deque *d, int val)
{
	if (d->size == d->capacity)
		resize(d, d->capacity * 2);
	d->arr[d->tail++] = val;
	if (d->tail == d->capacity)
		d->tail = 0;
	d->size++;
}

int	pop_front(t_deque *d)
{
	int		ret;

	if (d->capacity > g_memory_border
		&& d->size * 2 < d->capacity)
		resize(d, d->capacity / 2);
	ret = front(d);
	d->head++;
	if (d->head == d->capacity)
		d->head = 0;
	d->size--;
	return (ret);
}

void	push_front(t_deque *d, int val)
{
	if (d->size == d->capacity)
		resize(d, d->capacity * 2);
	d->head--;
	if (d->head < 0)
		d->head = d->capacity - 1;
	d->arr[d->head] = val;
	d->size++;
}

int	pop_back(t_deque *d)
{
	int		ret;

	if (d->capacity > g_memory_border
		&& d->size * 2 < d->capacity)
		resize(d, d->capacity / 2);
	ret = back(d);
	d->tail--;
	if (d->tail < 0)
		d->tail = d->capacity - 1;
	d->size--;
	return (ret);
}
