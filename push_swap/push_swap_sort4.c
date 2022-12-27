/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_sort4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 15:50:41 by gyopark           #+#    #+#             */
/*   Updated: 2022/12/27 14:41:57 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	push_min_a(t_deque *a, t_deque *b)
{
	int		min_a_idx;
	int		cnt;

	min_a_idx = get_min_a_idx(a);
	cnt = a->size - min_a_idx;
	if (min_a_idx >= a->size / 2)
	{
		while (cnt--)
			do_rra(a);
	}
	else
	{
		while (min_a_idx--)
			do_ra(a);
	}
	do_pa(a, b);
}

void	push_mid_a(t_deque *a, t_deque *b, int min_idx)
{
	int	up;
	int	down;

	up = check_a_up(a, b, min_idx);
	down = check_a_down(a, b, min_idx);
	if (ft_min(up, down) == up)
		while (up--)
			do_ra(a);
	else
	{
		while (down--)
		{
			do_rra(a);
			if (down == 0)
				break ;
		}
	}
	do_pa(a, b);
}

void	push_max_a(t_deque *a, t_deque *b)
{
	int		max_a_idx;
	int		cnt;

	max_a_idx = get_max_a_idx(a);
	cnt = a->size - max_a_idx - 1;
	if (max_a_idx < a->size / 2)
	{
		while (max_a_idx + 1)
		{
			do_ra(a);
			max_a_idx--;
		}
	}
	else
	{
		while (cnt--)
			do_rra(a);
	}
	do_pa(a, b);
}

#include <stdio.h>

int	check_case(int min_b, t_deque *a)
{
	int		a_case;
	int		a_size;
	int		idx;

	idx = 0;
	a_case = 0;
	a_size = a->size;
	/** printf("min_b : %d\n", min_b); */
	while (a_size--)
	{			
		if (front_idx(a, idx) <= min_b)
		{
			a_case++;
			idx++;
		}
		else
			idx++;
	}
	if (a_case == a->size)
		return (3);
	else if (a_case == 0)
		return (1);
	else
		return (2);
}
