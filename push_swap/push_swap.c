/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 21:56:49 by gyopark           #+#    #+#             */
/*   Updated: 2022/12/14 21:55:13 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdio.h>

const long long	g_max = 2147483647;
const long long	g_min = -2147483648;
const long long	g_ll = 3000000000;

void	ft_freeall(char **spl)
{
	size_t	j;

	j = 0;
	while (spl[j])
	{
		free(spl[j]);
		j++;
	}
	free(spl);
	return ;
}

long long	check_num(char *str)
{
	long long	l;
	long long	neg;

	if (*str == '-')
		neg = -1;
	else if (*str >= '0' && *str <= '9')
		neg = 1;
	else
		return (g_ll);
	if (*str != '-')
		--str;
	l = 0;
	while (*(++str))
	{
		if (*str < '0' || *str > '9')
			return (g_ll);
		l *= 10LL;
		l += *str - '0';
		if (l > -g_min)
			return (g_ll);
	}
	if ((neg < 0 && l <= -g_min) || (neg > 0 && l <= g_max))
		return (neg * l);
	else
		return (g_ll);
}

void	append_num(char *s, int *arr, int *idx)
{
	char		**spl;
	char		**save;
	long long	l;

	spl = ft_split(s, ' ');
	save = spl;
	--spl;
	while (*(++spl))
	{
		l = check_num(*spl);
		arr[(*idx)++] = l;
	}
	ft_freeall(save);
}

void	split_space(char *s, int *num)
{
	char		**spl;
	char		**save;
	long long	l;

	spl = ft_split(s, ' ');
	save = spl;
	if (!spl)
	{
		write(1, "Error\n", 6);
		exit(0);
	}
	--spl;
	while (*(++spl))
	{
		l = check_num(*spl);
		if (l == g_ll || ((*spl)[0] == '-' && (*spl)[1] == '\0'))
		{
			ft_freeall(save);
			write(1, "Error\n", 6);
			exit(0);
		}
		(*num)++;
	}
	ft_freeall(save);
}

int	main(int argc, char **argv)
{
	int	n;
	int	i;
	int	*arr;
	int	idx;

	i = 0;
	n = 0;
	while (++i < argc)
		split_space(argv[i], &n);
	printf("%d\n", n);
	i = 0;
	idx = 0;
	arr = (int *) malloc(sizeof(int) * n);
	while (++i < argc)
		append_num(argv[i], arr, &idx);
	/** for (int j = 0; j < n ;++j) */
	/** { */
	/**     printf("%d ", arr[j]); */
	/** } */
	dup_check(arr, n);
	free(arr);
	return (0);
}

/** void	print(t_deque *d) */
/** { */
/**     int		i; */
/**  */
/**     i = d->head - 1; */
/**     if (!empty(d)) */
/**     { */
/**         if (d->head < d->tail) */
/**             while (++i < d->tail) */
/**                 printf("%d ", d->arr[i]); */
/**         else */
/**         { */
/**             while (++i < d->capacity) */
/**                 printf("%d ", d->arr[i]); */
/**             i = -1; */
/**             while (++i < d->tail) */
/**                 printf("%d ", d->arr[i]); */
/**         } */
/**     } */
/**     printf("\n"); */
/** } */

/** int	main(void) */
/** { */
/**     t_deque	*d; */
/**  */
/**     d = make_deque(); */
/**     print(d); */
/**     push_back(d, 1); */
/**     push_back(d, 2); */
/**     push_back(d, 3); */
/**     push_back(d, 4); */
/**     print(d); */
/**     push_front(d, 5); */
/**     push_front(d, 6); */
/**     push_front(d, 7); */
/**     push_front(d, 8); */
/**     print(d); */
/**     return (0); */
/** } */
