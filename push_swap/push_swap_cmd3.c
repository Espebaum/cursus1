/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_cmd3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 18:42:17 by gyopark           #+#    #+#             */
/*   Updated: 2022/12/29 20:23:36 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	do_rrr(t_deque *a, t_deque *b)
{
	write(1, "rrr\n", 4);
	reverse_rotate(a);
	reverse_rotate(b);
}

int	ft_max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

int	is_bad_input(char *s)
{
	int		i;

	i = ft_strlen(s);
	while (i--)
	{
		if (s[i] != ' ')
			return (1);
	}
	return (0);
}
