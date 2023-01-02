/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_sort4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 15:50:41 by gyopark           #+#    #+#             */
/*   Updated: 2022/12/30 20:51:08 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	get_min_a_idx(t_deque *a)
{
	int		min_idx;
	int		i;

	i = -1;
	min_idx = 0;
	while (++i < a->size)
		if (front_idx(a, i) < front_idx(a, min_idx))
			min_idx = i;
	return (min_idx);
}

void	turn_min(t_deque *a, t_deque *cmd)
{
	int		min_idx;
	int		cnt;

	min_idx = get_min_a_idx(a);
	cnt = a->size - min_idx;
	if (min_idx >= a->size / 2)
		while (cnt--)
			do_rra(a, cmd);
	else
		while (min_idx--)
			do_ra(a, cmd);
}

int	check_case(int min_b, t_deque *a)
{
	int		a_case;
	int		a_size;
	int		idx;

	idx = 0;
	a_case = 0;
	a_size = a->size;
	while (a_size--)
	{			
		if (front_idx(a, idx) <= min_b)
			a_case++;
		idx++;
	}
	if (a_case == a->size)
		return (3);
	else if (a_case == 0)
		return (1);
	else
		return (2);
}
