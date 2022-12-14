/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_deque2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 17:07:02 by gyopark           #+#    #+#             */
/*   Updated: 2022/12/14 19:16:11 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	resize(t_deque *d, int new_cap)
{
	int		*new_arr;
	int		idx;
	int		i;

	new_arr = (int *) malloc(sizeof(int) * new_cap);
	idx = 0;
	i = d->head - 1;
	if (d->head < d->tail)
		while (++i < d->tail)
			new_arr[idx++] = d->arr[i];
	else
	{
		while (++i < d->capacity)
			new_arr[idx++] = d->arr[i];
		i = -1;
		while (++i < d->tail)
			new_arr[idx++] = d->arr[i];
	}
	free(d->arr);
	d->arr = new_arr;
	d->head = 0;
	d->tail = idx;
	d->capacity = new_cap;
}

void	rotate(t_deque *d)
{
	push_back(d, pop_front(d));
}

void	reverse_rotate(t_deque *d)
{
	push_front(d, pop_back(d));
}

//rotate
// 5 6 - - 1 2 3 4
//     t   h

// 5 6 - - 1 2 3 4
//     t     h

// 5 6 1 - 1 2 3 4
//       t   h
void	push(t_deque *from, t_deque *to)
{
	if (empty(from))
		return ;
	push_front(to, pop_front(from));
}

void	delete_deque(t_deque *d)
{
	free(d->arr);
	free(d);
}
