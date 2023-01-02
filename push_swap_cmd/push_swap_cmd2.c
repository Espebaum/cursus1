/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_cmd2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 18:36:39 by gyopark           #+#    #+#             */
/*   Updated: 2022/12/30 15:28:43 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	do_ra(t_deque *a, t_deque *cmd)
{
	push_back(cmd, RA);
	rotate(a);
}

void	do_rb(t_deque *a, t_deque *cmd)
{
	push_back(cmd, RB);
	rotate(a);
}

void	do_rr(t_deque *a, t_deque *b, t_deque *cmd)
{
	push_back(cmd, RR);
	rotate(a);
	rotate(b);
}

void	do_rra(t_deque *a, t_deque *cmd)
{
	push_back(cmd, RRA);
	reverse_rotate(a);
}

void	do_rrb(t_deque *b, t_deque *cmd)
{
	push_back(cmd, RRB);
	reverse_rotate(b);
}
