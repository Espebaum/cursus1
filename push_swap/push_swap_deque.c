/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_deque.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 15:14:23 by gyopark           #+#    #+#             */
/*   Updated: 2022/12/16 17:37:14 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_deque	*make_deque(void)
{
	t_deque	*ret;

	ret = (t_deque *) malloc(sizeof(t_deque));
	ret->size = 0;
	ret->head = 0;
	ret->tail = 0;
	ret->capacity = 32;
	ret->arr = (int *) malloc(sizeof(int) * ret->capacity);
	return (ret);
}

int	size(t_deque *d)
{
	return (d->size);
}

int	empty(t_deque *d)
{
	return (size(d) == 0);
}

int	front(t_deque *d)
{
	return (d->arr[d->head]);
}

int	back(t_deque *d)
{
	if (d->tail == 0)
		return (d->arr[d->capacity - 1]);
	else
		return (d->arr[d->tail - 1]);
}
// 제일 뒤에 있는 원소를 반환하는데, tail이 0일 경우 
// arr[capacity - 1]의 원소를 반환한다. tail이 0이라는 것은
// arr[capacity - 1]의 원소가 존재한다는 것을 의미한다.
