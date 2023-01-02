/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_utils1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 21:32:29 by gyopark           #+#    #+#             */
/*   Updated: 2022/12/31 16:55:02 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

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
