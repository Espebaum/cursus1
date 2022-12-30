/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 17:13:02 by gyopark           #+#    #+#             */
/*   Updated: 2022/12/30 14:32:50 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

int	get_min_idx(t_deque *a, t_deque *b)
{
	int		idx;
	int		b_cnt;
	int		sum_cnt;
	int		min_idx;
	int		temp;

	b_cnt = b->size;
	sum_cnt = 2147483647;
	idx = -1;
	while (++idx < b->size)
	{
		temp = sum_cnt;
		b_cnt = get_bcnt(b, idx);
		sum_cnt = ft_min(sum_cnt, b_cnt + check_a_cnt(idx, a, b));
		if (temp != sum_cnt)
			min_idx = idx;
	}
	return (min_idx);
}
