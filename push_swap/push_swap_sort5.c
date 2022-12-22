/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_sort5.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 18:07:13 by gyopark           #+#    #+#             */
/*   Updated: 2022/12/22 18:35:41 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	get_max_a_idx(t_deque *a)
{
	int		*arr;
	int		max_idx;
	int		i;

	i = -1;
	max_idx = 0;
	arr = (int *)malloc(sizeof(int) * a->size);
	deque_to_arr(a, arr);
	while (++i < a->size)
		if (arr[i] > arr[max_idx])
			max_idx = i;
	free(arr);
	return (max_idx);
}

int	get_min_a_idx(t_deque *a)
{
	int		*arr;
	int		min_idx;
	int		i;

	i = -1;
	min_idx = 0;
	arr = (int *)malloc(sizeof(int) * a->size);
	deque_to_arr(a, arr);
	while (++i < a->size)
		if (arr[i] < arr[min_idx])
			min_idx = i;
	free(arr);
	return (min_idx);
}

void	turn_min(t_deque *a)
{
	int		min_idx;
	int		cnt;

	min_idx = get_min_a_idx(a);
	cnt = a->size - min_idx;
	if (min_idx >= a->size / 2)
		while (cnt--)
			do_rra(a);
	else
		while (min_idx--)
			do_ra(a);
}
