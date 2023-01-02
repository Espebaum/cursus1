/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_print1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 21:42:08 by gyopark           #+#    #+#             */
/*   Updated: 2022/12/30 17:23:21 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	merge_cmd(t_deque *cmd, t_deque *cmd2)
{
	int	a;
	int	b;

	a = back(cmd2);
	b = front(cmd);
	if ((a == SA && b == SA) || (a == SB && b == SB))
	{
		pop_back(cmd2);
		pop_front(cmd);
		if (!empty(cmd) && !empty(cmd2))
			merge_cmd(cmd, cmd2);
	}
	else if ((a == SA && b == SS) || (a == SS && b == SA))
	{
		pop_back(cmd2);
		pop_front(cmd);
		push_back(cmd2, SB);
		if (!empty(cmd) && !empty(cmd2))
			merge_cmd(cmd, cmd2);
	}
	else
		merge_cmd_sub1(cmd, cmd2, a, b);
}

void	print_cmd_sub(int op)
{
	if (op == SA)
		write(1, "sa\n", 3);
	else if (op == SB)
		write(1, "sb\n", 3);
	else if (op == RA)
		write(1, "ra\n", 3);
	else if (op == RB)
		write(1, "rb\n", 3);
	else if (op == RRA)
		write(1, "rra\n", 4);
	else if (op == RRB)
		write(1, "rrb\n", 4);
	else if (op == PA)
		write(1, "pa\n", 3);
	else if (op == PB)
		write(1, "pb\n", 3);
	else if (op == RR)
		write(1, "rr\n", 3);
	else if (op == RRR)
		write(1, "rrr\n", 4);
	else if (op == SS)
		write(1, "ss\n", 3);
}

void	print_cmd(t_deque *cmd)
{
	int		idx;
	int		i;
	t_deque	*cmd2;

	cmd2 = make_deque();
	while (!empty(cmd))
	{
		push_back(cmd2, pop_front(cmd));
		if (!empty(cmd) && !empty(cmd2))
			merge_cmd(cmd, cmd2);
	}
	idx = cmd2->head;
	i = -1;
	while (++i < cmd2->size)
	{
		print_cmd_sub(cmd2->arr[idx++]);
		if (idx == cmd2->capacity)
			idx = 0;
	}
	delete_deque(cmd2);
}
