/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_cmd2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 18:36:39 by gyopark           #+#    #+#             */
/*   Updated: 2023/01/04 20:40:40 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	do_ra(t_deque *a)
{
	write(1, "ra\n", 3);
	rotate(a);
}

void	do_rb(t_deque *b)
{
	write(1, "rb\n", 3);
	rotate(b);
}

void	do_rr(t_deque *a, t_deque *b)
{
	write(1, "rr\n", 3);
	rotate(a);
	rotate(b);
}

void	do_rra(t_deque *deq)
{
	write(1, "rra\n", 4);
	reverse_rotate(deq);
}

void	do_rrb(t_deque *deq)
{
	write(1, "rrb\n", 4);
	reverse_rotate(deq);
}
