/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_sort.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 21:57:25 by gyopark           #+#    #+#             */
/*   Updated: 2022/12/27 16:02:21 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	is_sorted(int *arr, int size)
{
	int		i;
	int		j;

	i = 0;
	while (i < size - 1)
	{
		j = i + 1;
		while (j < size)
		{
			if (arr[i] > arr[j])
				return (size);
			j++;
		}
		i++;
	}
	return (1);
}

int	sort_arr(t_deque *a)
{
	int	*tmp_arr;
	int	arg;

	tmp_arr = (int *)malloc(sizeof(int) * a->size);
	deque_to_arr(a, tmp_arr);
	arg = is_sorted(tmp_arr, a->size);
	free(tmp_arr);
	return (arg);
}

void	*get_pivot(t_deque *a, int *pivot)
{
	int	*arr;

	arr = (int *) malloc(sizeof(int) * a->size);
	deque_to_arr(a, arr);
	my_qsort(arr, 0, a->size);
	pivot[0] = arr[a->size / 3];
	pivot[1] = arr[(a->size * 2) / 3];
	return (pivot);
}

int	start_sort(t_deque *a, t_deque *b, t_deque *deq_str)
{
	int	arg;
	int	idx1;
	int	idx2;

	idx1 = 0;
	idx2 = a->size - 1;
	if (front_idx(a, idx1) == front_idx(a, idx2))
		return (0);
	arg = sort_arr(a);
	if (arg == 1)
		return (0);
	else if (arg == 2)
		do_sa(a);
	else if (arg == 3)
		sort_3(a);
	else if (arg == 4)
		sort_4(a, b);
	else if (arg == 5)
		sort_5(a, b);
	else
		atob(a, b);
	deq_str = 0;
	return (0);
}
