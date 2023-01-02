/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_utils1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 21:32:29 by gyopark           #+#    #+#             */
/*   Updated: 2022/12/30 20:43:22 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	error_exit(t_deque *a)
{
	delete_deque(a);
	write(1, "Error\n", 6);
	exit(0);
}

void	dup_check(int *arr, int n, t_deque *a)
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
			error_exit(a);
		}
	}
	free(tmp_arr);
}

int	ft_min(int a, int b)
{
	if (a > b)
		return (b);
	return (a);
}

int	ft_max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}
