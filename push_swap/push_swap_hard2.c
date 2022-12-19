/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_hard2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 15:00:52 by gyopark           #+#    #+#             */
/*   Updated: 2022/12/18 15:01:35 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	sort_5(t_deque *a, t_deque *b)
{
	int		i;
	int		arr[5];

	if (is_sorted_deq(a))
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
	if (!is_sorted_deq(a))
		sort_3(a);
	if (front_idx(b, 0) < front_idx(b, 1))
		do_sb(b);
	do_pa(a, b);
	do_pa(a, b);
	return (0);
}
