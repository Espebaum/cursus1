/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 15:11:59 by gyopark           #+#    #+#             */
/*   Updated: 2023/01/01 17:19:29 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned int	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			break ;
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	is_sorted_arr(t_deque *a, int size)
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

void	check_condition(t_deque *a, t_deque *b)
{
	if (is_sorted_arr(a, a->size) == 1 && !b->size)
		write(1, "OK\n", 3);
	else
		write(1, "KO\n", 3);
}

void	check_cmd(char *line, t_deque *a, t_deque *b, t_deque *cmd)
{
	if (ft_strcmp(line, "sa\n") == 0)
		do_sa(a, cmd);
	else if (ft_strcmp(line, "sb\n") == 0)
		do_sb(b, cmd);
	else if (ft_strcmp(line, "ra\n") == 0)
		do_ra(a, cmd);
	else if (ft_strcmp(line, "rb\n") == 0)
		do_rb(b, cmd);
	else if (ft_strcmp(line, "rra\n") == 0)
		do_rra(a, cmd);
	else if (ft_strcmp(line, "rrb\n") == 0)
		do_rrb(b, cmd);
	else if (ft_strcmp(line, "pa\n") == 0)
		do_pa(a, b, cmd);
	else if (ft_strcmp(line, "pb\n") == 0)
		do_pb(a, b, cmd);
	else if (ft_strcmp(line, "rr\n") == 0)
		do_rr(a, b, cmd);
	else if (ft_strcmp(line, "rrr\n") == 0)
		do_rrr(a, b, cmd);
	else if (ft_strcmp(line, "ss\n") == 0)
		do_ss(a, b, cmd);
	else
		error_exit(a);
}
