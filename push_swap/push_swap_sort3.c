/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_sort3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 15:29:42 by gyopark           #+#    #+#             */
/*   Updated: 2022/12/21 21:54:48 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdio.h>

int	check_a_up(t_deque *a, t_deque *b, int idx)
{
	int	a_size;
	int	a_head;
	int	a_cnt;

	a_cnt = 0;
	a_head = a->head;
	a_size = a->size;
	while (a_size--)
	{
		if (a->arr[a_head] < front_idx(b, idx))
		{
			a_cnt++;
			a_head++;
			if (a_head == a->capacity)
				a_head = 0;
		}
	}
	return (a_cnt);
}


int	check_a_down(t_deque *a, t_deque *b, int idx)
{
	int	a_size;
	int	a_head;
	int	a_tail;
	int	a_cnt;

	a_cnt = 0;
	a_head = a->head;
	a_tail = a->tail - 1;
	a_size = a->size;
	while (a_size--)
	{
		if (a->arr[a_tail] > front_idx(b, idx)
			|| (a->arr[a_tail] < front_idx(b, idx)
				&& a->arr[a_head] < front_idx(b, idx)))
		{
			a_cnt++;
			a_tail--;
			if (a_tail < 0)
				a_tail = a->capacity;
		}
	}
	return (a_cnt);
}

void	push_a(t_deque *a, t_deque *b, int min_idx)
{
	int		a_case;
	int		a_size; //check
	int		b_size; //check
	int		i;		//check

	a_case = check_case(front_idx(b, min_idx), a);
	printf("\na_case : %d\n", a_case);
	if (a->size == 1)
	{
		if (a->arr[a->head] < b->arr[b->head])
		{
			do_pa(a, b);
			do_sa(a);
		}
		else
			do_pa(a, b);
		//체크
		a_size = a->size;
		i = 0;
		printf("옮겨진 a stack : ");
		while (a_size--)
		{
			printf("%d ", front_idx(a, i++));
		}
		printf("\n(초회)\n\n");
		return ;
	}
	if (a_case == 3)
		push_max_a(a, b);
	else if (a_case == 1)
		push_min_a(a, b);
	else
		push_mid_a(a, b, min_idx);
	//체크
	a_size = a->size;
	i = 0;
	printf("옮겨진 a stack(회차 끝) : ");
	while (a_size--)
	{
		printf("%d ", front_idx(a, i++));
	}
	printf("\na head %d\n", a->arr[a->head]);
	printf("\n");
	b_size = b->size;
	i = 0;
	printf("남은 b stack(회차 끝) : ");
	while (b_size--)
	{
		printf("%d ", front_idx(b, i++));
	}
	printf("\nb head %d\n", b->arr[b->head]);
	printf("\n");
}

void	push_min_b(t_deque *a, t_deque *b, int min_idx)
{
	int		b_size; //체크
	int		i; //체크
	int		min;
	
	min = min_idx;
	//체크
	b_size = b->size;
	i = 0;
	printf("b stack : ");
	while (b_size--)
	{
		printf("%d ", front_idx(b, i++));
	}
	printf("\n");
	//체크 끝
	
	if (min_idx < b->size / 2)
		while (min--)
			do_rb(b);
	else
		while (min--)
			do_rrb(b);

	//체크 시작
	b_size = b->size;
	i = 0;
	printf("제일 작은 명령어가 제일 위인 b stack : ");
	while (b_size--)
	{
		printf("%d ", front_idx(b, i++));
	}
	printf("\n");
	push_a(a, b, min_idx);
}
