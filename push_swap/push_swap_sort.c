/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_sort.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 21:57:25 by gyopark           #+#    #+#             */
/*   Updated: 2022/12/29 20:40:50 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	is_sorted(t_deque *a, int size)
{
	int		i;
	int		j;

	i = 0;
	while (i < size - 1)
	{
		j = i + 1;
		while (j < size)
		{
			if (front_idx(a, i) > front_idx(a, j))
				return (size);
			j++;
		}
		i++;
	}
	return (1);
}

int	sort_arr(t_deque *a)
{
	int		arg;

	arg = is_sorted(a, a->size);
	return (arg);
}

/** void	get_pivot(t_deque *a, int *pivot, int *arr) */
/** { */
/**     int	pivot1; */
/**     int	pivot2; */
/**  */
/**     deque_to_arr(a, arr); */
/**     my_qsort(arr, 0, a->size); */
/**     pivot1 = arr[a->size / 3]; */
/**     pivot2 = arr[(a->size * 2) / 3]; */
/**     pivot[0] = pivot1; */
/**     pivot[1] = pivot2; */
/** } */

int	start_sort(t_deque *a, t_deque *b)
{
	int	arg;

	arg = sort_arr(a);
	if (arg == 2)
		do_sa(a);
	else if (arg == 3)
		sort_3(a);
	else if (arg == 4)
		sort_4(a, b);
	else if (arg == 5)
		sort_5(a, b);
	else if (arg > 5)
		atob(a, b);
	return (0);
}
