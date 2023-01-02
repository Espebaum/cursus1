/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_cmd1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 14:12:21 by gyopark           #+#    #+#             */
/*   Updated: 2022/12/31 15:34:15 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

void	do_sa(t_deque *a, t_deque *cmd)
{
	push_back(cmd, SA);
	swap_top(a);
}

void	do_sb(t_deque *b, t_deque *cmd)
{
	push_back(cmd, SB);
	swap_top(b);
}

void	do_ss(t_deque *a, t_deque *b, t_deque *cmd)
{
	push_back(cmd, SS);
	swap_top(a);
	swap_top(b);
}

void	do_pa(t_deque *a, t_deque *b, t_deque *cmd)
{
	push_back(cmd, PA);
	push(b, a);
}

void	do_pb(t_deque *a, t_deque *b, t_deque *cmd)
{
	push_back(cmd, PB);
	push(a, b);
}
