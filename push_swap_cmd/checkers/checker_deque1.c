/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_deque1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 15:14:23 by gyopark           #+#    #+#             */
/*   Updated: 2022/12/31 15:10:03 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

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
