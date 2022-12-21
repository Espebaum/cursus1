/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_sort4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 15:50:41 by gyopark           #+#    #+#             */
/*   Updated: 2022/12/21 21:59:21 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdio.h>

void	push_min_a(t_deque *a, t_deque *b)
{
	int		min_a_idx;
	int		cnt;

	min_a_idx = get_min_a_idx(a);
	cnt = a->size - min_a_idx;
	printf("\nmin_a_idx : %d, cnt : %d\n", min_a_idx, cnt);
	if (min_a_idx > a->size / 2)
	{
		printf("min cnt %d\n", cnt);
		while (cnt--)
			do_rra(a);
	}
	else
	{
		while (min_a_idx)
		{
			do_ra(a);
			min_a_idx--;
		}
	}
	do_pa(a, b);
}

void	push_mid_a(t_deque *a, t_deque *b, int min_idx)
{
	int	up;
	int	down;

	up = check_a_up(a, b, min_idx);
	down = check_a_down(a, b, min_idx);
	printf("\nup : %d down : %d\n", up, down);
	if (ft_min(up, down) == up)
		while (up--)
			do_ra(a);
	else
	{
		while (down--)
		{
			printf("down %d\n", down);
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
	printf("\na->size : %d max_a_idx : %d\n", a->size, max_a_idx);
	if (max_a_idx > a->size / 2)
	{
		printf("maxcnt %d\n", cnt);
		while (cnt--)
			do_rra(a);
	}
	else
	{
		while (max_a_idx + 1)
		{
			do_ra(a);
			max_a_idx--;
		}
	}
	do_pa(a, b);
}

int	check_case(int b_idx, t_deque *a)
{
	int		a_case;
	int		a_head;
	int		a_size;

	a_case = 0;
	a_size = a->size;
	a_head = a->head;
	while (a_size--)
	{
		if (a->arr[a_head] < b_idx)
		{
			a_case++;
			a_head++;
			if (a_head == a->capacity)
				a_head = 0;
		}
	}
	printf("a->size : %d a_case : %d\n", a->size, a_case);
	if (a_case == a->size)
		return (3);
	else if (a_case == 0)
		return (1);
	else
		return (2);
}
