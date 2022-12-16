/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_qsort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 20:29:31 by gyopark           #+#    #+#             */
/*   Updated: 2022/12/16 15:32:42 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	my_qsort(int *arr, int L, int R)
{
	int	left = L, right = R;
	int	pivot = arr[(L + R) / 2];
	int	temp;

	if (L >= R)
		return ;
	while (L <= R)
	{
		while (arr[L] < pivot)
			L++;
		while (arr[R] > pivot)
			R--;
		if (L <= R)
		{
			temp = arr[L];
			arr[L] = arr[R];
			arr[R] = temp;
			L++;
			R--;
		}
	}
	if (left < R)
		my_qsort(arr, left, R);
	if (L < right)
		my_qsort(arr, L, right);
}

int	main(int argc, char **argv)
{
	int		*arr;
	int		i;
	char	c;

	i = 0;
	if (argc == 1)
		return (write(1, "Error\n", 6));
	arr = (int *) malloc(sizeof(int) * (argc - 1));
	while (i < argc - 1)
	{
		c = **(argv + i + 1);
		printf("%c ", **(argv + i + 1));
		arr[i] = c;
		i++;
		(*argv)++;
	}
	
	printf("\n");
	my_qsort(arr, 0, argc - 1);
	
	i = 0;
	while (i < argc)
	{
		printf("%c ", arr[i++]);
	}
	printf("\n");
	free(arr);
	return (0);
}
