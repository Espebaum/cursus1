/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 21:57:08 by gyopark           #+#    #+#             */
/*   Updated: 2022/12/31 17:20:57 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKER_H
# define CHECKER_H

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

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4
# endif

# ifndef OPEN_MAX
#  define OPEN_MAX 10240
# endif

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
void	my_qsort(int *arr, int left, int right);
int		front_idx(t_deque *deq, int idx);
void	deque_to_arr(t_deque *d, int *a);
int		is_sorted_deq(t_deque *a);

void	check_cmd(char *line, t_deque *a, t_deque *b, t_deque *cmd);
char	*get_next_line(int fd);
void	*ft_memcpy(void *dest, const void *src, size_t n);
char	*ft_strchr(const char *s, int c);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char *s1, char *s2);
void	str_free(char **str);
void	check_condition(t_deque *a, t_deque *b);

#endif
