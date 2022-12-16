/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 21:57:08 by gyopark           #+#    #+#             */
/*   Updated: 2022/12/16 17:03:47 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

#include <stdlib.h>
#include <unistd.h>
// #include "./libft/libft.h"

typedef struct s_deque
{
	int		*arr;
	int		head;
	int		tail;
	int		size;
	int		capacity;
}			t_deque;

t_deque	*make_deque(void);
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
void	rotate(t_deque *d);
void	reverse_rotate(t_deque *d);
void	delete_deque(t_deque *d);
void	dup_check(int *arr, int n);
void	push_arr_deq(int *arr, int argc, t_deque *deq);

char	*ft_substr(char const *s, unsigned int start, size_t len);
char	**ft_split(char const *s, char c);

#endif
