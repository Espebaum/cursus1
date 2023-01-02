/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_cmd1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 14:12:21 by gyopark           #+#    #+#             */
/*   Updated: 2023/01/01 20:27:42 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	do_sa(t_deque *a)
{
	write(1, "sa\n", 3);
	swap_top(a);
}

void	do_sb(t_deque *b)
{
	write(1, "sb\n", 3);
	swap_top(b);
}

void	do_ss(t_deque *a, t_deque *b)
{
	write(1, "ss\n", 3);
	do_sa(a);
	do_sa(b);
}

void	do_pa(t_deque *a, t_deque *b)
{
	write(1, "pa\n", 3);
	push(b, a);
}

void	do_pb(t_deque *a, t_deque *b)
{
	write(1, "pb\n", 3);
	push(a, b);
}
