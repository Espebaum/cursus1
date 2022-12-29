/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_sort5.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 18:07:13 by gyopark           #+#    #+#             */
/*   Updated: 2022/12/29 16:47:43 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	get_min_a_idx(t_deque *a)
{
	int		min_idx;
	int		i;

	i = -1;
	min_idx = 0;
	while (++i < a->size)
		if (front_idx(a, i) < front_idx(a, min_idx))
			min_idx = i;
	return (min_idx);
}

void	turn_min(t_deque *a)
{
	int		min_idx;
	int		cnt;

	min_idx = get_min_a_idx(a);
	cnt = a->size - min_idx;
	if (min_idx >= a->size / 2)
		while (cnt--)
			do_rra(a);
	else
		while (min_idx--)
			do_ra(a);
}

/** void	bflag_check(t_deque *b, int min_idx, int *b_flag) */
/** { */
/**     int	b_cnt; */
/**  */
/**     b_cnt = get_bcnt(b, min_idx, b_flag); */
/** } */
/**  */
/** void	aflag_check(t_deque *a, t_deque *b, int min_idx, int *a_flag) */
/** { */
/**     int	a_cnt; */
/**  */
/**     a_cnt = check_a_cnt(min_idx, a, b, a_flag); */
/** } */
