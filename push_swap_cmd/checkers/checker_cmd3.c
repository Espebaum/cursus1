/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_cmd3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 18:42:17 by gyopark           #+#    #+#             */
/*   Updated: 2022/12/31 15:10:06 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

void	do_rrr(t_deque *a, t_deque *b, t_deque *cmd)
{
	push_back(cmd, RRR);
	reverse_rotate(a);
	reverse_rotate(b);
}
