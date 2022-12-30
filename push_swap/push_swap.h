/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 21:57:08 by gyopark           #+#    #+#             */
/*   Updated: 2022/12/30 14:27:14 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

#include <stdlib.h>
#include <unistd.h>

typedef struct s_deque
{
	int		*arr;
	int		head;
	int		tail;
	int		size;
	int		capacity;
}			t_deque;

t_deque	*make_deque(void);
int		isdigit(int c);
int		front(t_deque *d);
int		back(t_deque *d);
int		size(t_deque *d);
int		empty(t_deque *d);
void	swap_top(t_deque *d);
void	resize(t_deque *d, int new_cap);
void	push_back(t_deque *d, int val);
int		pop_front(t_deque *d);
void	push_front(t_deque *d, int val);
int		pop_back(t_deque *d);
void	push(t_deque *from, t_deque *to);
void	rotate(t_deque *d);
void	reverse_rotate(t_deque *d);
void	delete_deque(t_deque *d);
void	dup_check(int *arr, int n, t_deque *a);
void	push_arr_deq(int *arr, int argc, t_deque *deq);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	**ft_split(char const *s, char c);
size_t	ft_strlen(const char *s);
int		is_bad_input(char *s);
int		error_exit(t_deque *a);

int		start_sort(t_deque *deq_a, t_deque *deq_b);
void	do_sa(t_deque *deq);
void	do_sb(t_deque *deq);
void	do_ss(t_deque *a, t_deque *b);
void	do_pa(t_deque *a, t_deque *b);
void	do_pb(t_deque *a, t_deque *b);
void	do_ra(t_deque *deq);
void	do_rb(t_deque *deq);
void	do_rr(t_deque *a, t_deque *b);
void	do_rra(t_deque *deq);
void	do_rrb(t_deque *deq);
void	do_rrr(t_deque *a, t_deque *b);

int		is_sorted_deq(t_deque *a);
int		sort_3(t_deque *deq);
int		sort_4(t_deque *a, t_deque *b);
int		sort_5(t_deque *a, t_deque *b);
int		ft_min(int a, int b);
int		ft_max(int a, int b);
void	my_qsort(int *arr, int left, int right);
int		front_idx(t_deque *deq, int idx);
void	deque_to_arr(t_deque *d, int *a);
int		is_sorted_deq(t_deque *a);

void	atob(t_deque *a, t_deque *b);
void	get_pivot(t_deque *a, int *pivot, int *arr);
int		get_bcnt(t_deque *b, int idx);
int		check_a_up(t_deque *a, t_deque *b, int idx);
int		get_min_idx(t_deque *a, t_deque *b);
int		check_a_down(t_deque *a, t_deque *b, int idx);
int		check_case(int b_idx, t_deque *a);
int		check_a_cnt(int idx, t_deque *a, t_deque *b);
void	push_min_b(t_deque *a, t_deque *b, int temp);
void	push_a(t_deque *a, t_deque *b, int min_idx);
void	push_min_a(t_deque *a, t_deque *b);
void	push_mid_a(t_deque *a, t_deque *b, int min_idx);
void	push_max_a(t_deque *a, t_deque *b);
int		get_max_a_idx(t_deque *a);
int		get_min_a_idx(t_deque *a);
void	turn_min(t_deque *a);

void	merge_rr(t_deque *a, t_deque *b, int min_idx, int temp);

#endif
