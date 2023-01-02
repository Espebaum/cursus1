/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 17:13:02 by gyopark           #+#    #+#             */
/*   Updated: 2022/12/30 20:04:41 by gyopark          ###   ########.fr       */
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

int	is_bad_input(char *s)
{
	int		i;

	i = ft_strlen(s);
	if (*s == '\0')
		return (1);
	while (i--)
	{
		if (s[i] != ' ')
			return (0);
	}
	return (1);
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

void	get_pivot(t_deque *a, int *pivot, int *arr)
{
	deque_to_arr(a, arr);
	my_qsort(arr, 0, a->size - 1);
	pivot[0] = arr[a->size / 3];
	pivot[1] = arr[a->size / 3 * 2];
	free(arr);
}
