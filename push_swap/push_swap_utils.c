/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 21:32:29 by gyopark           #+#    #+#             */
/*   Updated: 2022/12/15 22:26:45 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdio.h>

void	push_arr_deq(int *arr, int size, t_deque *deq)
{
	int		i;

	i = 0;
	while (size)
	{
		deq->arr[i] = arr[size - 1];
		i++;
		size--;
	}
}

void	my_qsort(int *arr, int left, int right)
{
	int		l;
	int		r;
	int		mid;
	int		tmp;

	if (left >= right)
		return ;
	l = left - 1;
	r = right + 1;
	mid = arr[(l + r) / 2];
	while (1)
	{
		while (arr[++l] < mid)
			;
		while (arr[--r] > mid)
			;
		if (l >= r)
			break ;
		tmp = arr[l];
		arr[l] = arr[r];
		arr[r] = tmp;
	}
	my_qsort(arr, left, l - 1);
	my_qsort(arr, r + 1, right);
}

void	dup_check(int *arr, int n)
{
	int		*tmp_arr;
	int		i;

	tmp_arr = (int *) malloc(sizeof(int) * n);
	i = -1;
	while (++i < n)
		tmp_arr[i] = arr[i];
	my_qsort(tmp_arr, 0, n - 1);
	i = 0;
	while (++i < n)
	{
		if (tmp_arr[i - 1] == tmp_arr[i])
		{
			free(arr);
			free(tmp_arr);
			write(1, "Error\n", 6);
			exit(0);
		}
	}
	free(tmp_arr);
}
