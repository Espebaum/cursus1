/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_print2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 22:07:51 by gyopark           #+#    #+#             */
/*   Updated: 2022/12/30 15:12:03 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	merge_cmd_sub4(t_deque *cmd, t_deque *cmd2, int a, int b)
{
	if ((a == RRR && b == RA) || (a == RA && b == RRR))
	{
		pop_back(cmd2);
		pop_front(cmd);
		push_back(cmd2, RRB);
		if (!empty(cmd) && !empty(cmd2))
			merge_cmd(cmd, cmd2);
	}
	else if ((a == RRR && b == RB) || (a == RB && b == RRR))
	{
		pop_back(cmd2);
		pop_front(cmd);
		push_back(cmd2, RRA);
		if (!empty(cmd) && !empty(cmd2))
			merge_cmd(cmd, cmd2);
	}
	else if ((a == RR && b == RRR) || (a == RRR && b == RR))
	{
		pop_back(cmd2);
		pop_front(cmd);
		if (!empty(cmd) && !empty(cmd2))
			merge_cmd(cmd, cmd2);
	}
}

void	merge_cmd_sub3(t_deque *cmd, t_deque *cmd2, int a, int b)
{
	if ((a == RR && b == RRA) || (a == RRA && b == RR))
	{
		pop_back(cmd2);
		pop_front(cmd);
		push_back(cmd2, RB);
		if (!empty(cmd) && !empty(cmd2))
			merge_cmd(cmd, cmd2);
	}
	else if ((a == RR && b == RRB) || (a == RRB && b == RR))
	{
		pop_back(cmd2);
		pop_front(cmd);
		push_back(cmd2, RA);
		if (!empty(cmd) && !empty(cmd2))
			merge_cmd(cmd, cmd2);
	}
	else if ((a == RB && b == RRB) || (a == RRB && b == RB))
	{
		pop_back(cmd2);
		pop_front(cmd);
		if (!empty(cmd) && !empty(cmd2))
			merge_cmd(cmd, cmd2);
	}
	else
		merge_cmd_sub4(cmd, cmd2, a, b);
}

void	merge_cmd_sub2(t_deque *cmd, t_deque *cmd2, int a, int b)
{
	if ((a == RA && b == RB) || (a == RB && b == RA))
	{
		pop_back(cmd2);
		pop_front(cmd);
		push_back(cmd2, RR);
		if (!empty(cmd) && !empty(cmd2))
			merge_cmd(cmd, cmd2);
	}
	else if ((a == RRA && b == RRB) || (a == RRB && b == RRA))
	{
		pop_back(cmd2);
		pop_front(cmd);
		push_back(cmd2, RRR);
		if (!empty(cmd) && !empty(cmd2))
			merge_cmd(cmd, cmd2);
	}
	else if ((a == RA && b == RRA) || (a == RRA && b == RA))
	{
		pop_back(cmd2);
		pop_front(cmd);
		if (!empty(cmd) && !empty(cmd2))
			merge_cmd(cmd, cmd2);
	}
	else
		merge_cmd_sub3(cmd, cmd2, a, b);
}

void	merge_cmd_sub1(t_deque *cmd, t_deque *cmd2, int a, int b)
{
	if ((a == SB && b == SS) || (a == SS && b == SB))
	{
		pop_back(cmd2);
		pop_front(cmd);
		push_back(cmd2, SA);
		if (!empty(cmd) && !empty(cmd2))
			merge_cmd(cmd, cmd2);
	}
	else if ((a == SB && b == SA) || (a == SA && b == SB))
	{
		pop_back(cmd2);
		pop_front(cmd);
		push_back(cmd2, SS);
		if (!empty(cmd) && !empty(cmd2))
			merge_cmd(cmd, cmd2);
	}
	else if ((a == PA && b == PB) || (a == PB && b == PA))
	{
		pop_back(cmd2);
		pop_front(cmd);
		if (!empty(cmd) && !empty(cmd2))
			merge_cmd(cmd, cmd2);
	}
	else
		merge_cmd_sub2(cmd, cmd2, a, b);
}
