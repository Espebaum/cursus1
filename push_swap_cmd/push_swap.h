/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 21:57:08 by gyopark           #+#    #+#             */
/*   Updated: 2022/12/30 20:56:41 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>
# include <unistd.h>

typedef struct s_deque
{
	int		*arr;
	int		head;
	int		tail;
	int		size;
	int		capacity;
}			t_deque;

typedef enum e_cmd {
	SA,
	SB,
	RA,
	RB,
	RRA,
	RRB,
	PA,
	PB,
	RR,
	RRR,
	SS
}	t_cmd;

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
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	**ft_split(char const *s, char c);
void	ft_freeall(char **spl);
size_t	ft_strlen(const char *s);
int		is_bad_input(char *s);
int		error_exit(t_deque *a);

int		start_sort(t_deque *deq_a, t_deque *deq_b, t_deque *cmd);
void	do_sa(t_deque *deq, t_deque *cmd);
void	do_sb(t_deque *deq, t_deque *cmd);
void	do_ss(t_deque *a, t_deque *b, t_deque *cmd);
void	do_pa(t_deque *a, t_deque *b, t_deque *cmd);
void	do_pb(t_deque *a, t_deque *b, t_deque *cmd);
void	do_ra(t_deque *deq, t_deque *cmd);
void	do_rb(t_deque *deq, t_deque *cmd);
void	do_rr(t_deque *a, t_deque *b, t_deque *cmd);
void	do_rra(t_deque *deq, t_deque *cmd);
void	do_rrb(t_deque *deq, t_deque *cmd);
void	do_rrr(t_deque *a, t_deque *b, t_deque *cmd);

int		is_sorted_arr(t_deque *a, int size);
int		sort_3(t_deque *deq, t_deque *cmd);
int		sort_4(t_deque *a, t_deque *b, t_deque *cmd);
int		sort_5(t_deque *a, t_deque *b, t_deque *cmd);
int		ft_min(int a, int b);
int		ft_max(int a, int b);
void	my_qsort(int *arr, int left, int right);
int		front_idx(t_deque *deq, int idx);
void	deque_to_arr(t_deque *d, int *a);
int		is_sorted_deq(t_deque *a);

void	atob(t_deque *a, t_deque *b, t_deque *cmd);
void	get_pivot(t_deque *a, int *pivot, int *arr);
int		get_min_idx(t_deque *a, t_deque *b);
int		get_bcnt(t_deque *b, int idx);
int		same_cnt(t_deque *a, t_deque *b, int min_idx);
int		check_a_up(t_deque *a, t_deque *b, int idx);
int		check_a_down(t_deque *a, t_deque *b, int idx);
int		check_case(int b_idx, t_deque *a);
int		check_a_cnt(int idx, t_deque *a, t_deque *b);
void	push_min_b(t_deque *a, t_deque *b, t_deque *cmd);
void	push_a(t_deque *a, t_deque *b, t_deque *cmd, int min_idx);
void	push_min_a(t_deque *a, t_deque *b, t_deque *cmd, int min_a_idx);
void	push_mid_a(t_deque *a, t_deque *b, t_deque *cmd);
void	push_max_a(t_deque *a, t_deque *b);
int		get_max_a_idx(t_deque *a);
int		get_min_a_idx(t_deque *a);
void	turn_min(t_deque *a, t_deque *cmd);

void	merge_rr(t_deque *a, t_deque *b, t_deque *cmd, int temp);
void	print_cmd(t_deque *cmd);
void	merge_cmd(t_deque *cmd, t_deque *cmd2);
void	merge_cmd_sub1(t_deque *cmd, t_deque *cmd2, int a, int b);

#endif
