/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_sort5.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 18:07:13 by gyopark           #+#    #+#             */
/*   Updated: 2022/12/21 22:19:04 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdio.h>

int	get_max_a_idx(t_deque *a)
{
	int		*arr;
	int		max;
	int		i;

	i = 0;
	arr = (int *)malloc(sizeof(int) * a->size);
	max = -2147483648;
	deque_to_arr(a, arr);
	if (i < a->size - 1)
	{
		max = ft_max(arr[i], arr[i + 1]);
		i++;
	}
	free(arr);
	printf("max i : %d\n", i);
	return (i);
}

int	get_min_a_idx(t_deque *a)
{
	int		*arr;
	int		min;
	int		i;

	i = 0;
	arr = (int *)malloc(sizeof(int) * a->size);
	min = 2147483647;
	deque_to_arr(a, arr);
	if (i < a->size - 1)
	{
		printf("\narr[i] : %d arr[i + 1] : %d\n", arr[i], arr[i + 1]);
		min = ft_max(arr[i], arr[i + 1]);
		i++;
	}
	free(arr);
	return (i);
}
// 12/22일 여기서부터 봐야함
