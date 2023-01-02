/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwkim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 19:23:49 by juwkim            #+#    #+#             */
/*   Updated: 2022/12/29 20:03:55 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

const int		g_memory_border = 1024;
const long long	g_max = 2147483647;
const long long	g_min = -2147483648;
const long long	g_ll = 3000000000;
const int		g_sa = 0;
const int		g_sb = 1;
const int		g_ra = 2;
const int		g_rb = 3;
const int		g_rra = 4;
const int		g_rrb = 5;
const int		g_pa = 6;
const int		g_pb = 7;
const int		g_rr = 8;
const int		g_rrr = 9;
const int		g_ss = 10;

typedef struct s_deque
{
	int		*arr;
	int		head;
	int		tail;
	int		size;
	int		capacity;
}				t_deque;

t_deque	*make_deque(void)
{
	t_deque		*ret;

	ret = (t_deque *) malloc(sizeof(t_deque));
	ret->size = 0;
	ret->head = 0;
	ret->tail = 0;
	ret->capacity = 32;
	ret->arr = (int *) malloc(sizeof(int) * ret->capacity);
	return (ret);
}

int	size(t_deque *d)
{
	return (d->size);
}

int	empty(t_deque *d)
{
	return (size(d) == 0);
}

int	front(t_deque *d)
{
	return (d->arr[d->head]);
}

int	back(t_deque *d)
{
	if (d->tail == 0)
		return (d->arr[d->capacity - 1]);
	else
		return (d->arr[d->tail - 1]);
}

void	swap_top(t_deque *d)
{
	int		tmp;
	int		idx1;
	int		idx2;

	idx1 = d->head;
	if (idx1 == d->capacity - 1)
		idx2 = 0;
	else
		idx2 = idx1 + 1;
	tmp = d->arr[idx1];
	d->arr[idx1] = d->arr[idx2];
	d->arr[idx2] = tmp;
}

void	resize(t_deque *d, int new_cap)
{
	int		*new_arr;
	int		idx;
	int		i;

	new_arr = (int *) malloc(sizeof(int) * new_cap);
	idx = 0;
	i = d->head - 1;
	if (d->head < d->tail)
		while (++i < d->tail)
			new_arr[idx++] = d->arr[i];
	else
	{
		while (++i < d->capacity)
			new_arr[idx++] = d->arr[i];
		i = -1;
		while (++i < d->tail)
			new_arr[idx++] = d->arr[i];
	}
	free(d->arr);
	d->arr = new_arr;
	d->head = 0;
	d->tail = idx;
	d->capacity = new_cap;
}

void	push_back(t_deque *d, int val)
{
	if (d->size == d->capacity)
		resize(d, d->capacity * 2);
	d->arr[d->tail++] = val;
	if (d->tail == d->capacity)
		d->tail = 0;
	d->size++;
}

int	pop_front(t_deque *d)
{
	int		ret;

	if (d->capacity > g_memory_border && d->size * 2 < d->capacity)
		resize(d, d->capacity / 2);
	ret = front(d);
	d->head++;
	if (d->head == d->capacity)
		d->head = 0;
	d->size--;
	return (ret);
}

void	push_front(t_deque *d, int val)
{
	if (d->size == d->capacity)
		resize(d, d->capacity * 2);
	d->head--;
	if (d->head < 0)
		d->head = d->capacity - 1;
	d->arr[d->head] = val;
	d->size++;
}

int	pop_back(t_deque *d)
{
	int		ret;

	if (d->capacity > g_memory_border && d->size * 2 < d->capacity)
		resize(d, d->capacity / 2);
	ret = back(d);
	d->tail--;
	if (d->tail < 0)
		d->tail = d->capacity - 1;
	d->size--;
	return (ret);
}

void	rotate(t_deque *d)
{
	push_back(d, pop_front(d));
}

void	reverse_rotate(t_deque *d)
{
	push_front(d, pop_back(d));
}

void	push(t_deque *from, t_deque *to)
{
	if (empty(from))
		return ;
	push_front(to, pop_front(from));
}

void	print(t_deque *d)
{
	int		i;

	printf("size: %d, cap: %d\t", d->size, d->capacity);
	i = d->head - 1;
	if (!empty(d))
	{
		if (d->head < d->tail)
			while (++i < d->tail)
				printf("%d ", d->arr[i]);
		else
		{
			while (++i < d->capacity)
				printf("%d ", d->arr[i]);
			i = -1;
			while (++i < d->tail)
				printf("%d ", d->arr[i]);
		}
	}
	printf("\n");
}

void	delete_deque(t_deque *d)
{
	free(d->arr);
	free(d);
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

size_t	ft_strlen(const char *s)
{
	size_t	cnt;

	cnt = 0;
	while (*s++)
		cnt++;
	return (cnt);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	char	*c;
	size_t	cnt;

	c = (char *)src;
	cnt = 0;
	while (*c)
	{
		c++;
		cnt++;
	}
	if (size)
	{
		while (*src && --size)
		{
			*dest = *src;
			src++;
			dest++;
		}
		*dest = '\0';
	}
	return (cnt);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*new_dest;
	unsigned char	*new_src;
	size_t			i;

	if (dest == src)
		return (dest);
	new_dest = (unsigned char *) dest;
	new_src = (unsigned char *) src;
	i = 0;
	while (i++ < n)
		*new_dest++ = *new_src++;
	return (dest);
}

char	*ft_strdup(const char *s1)
{
	size_t	s1_len;
	char	*mem;

	s1_len = ft_strlen(s1);
	mem = (char *)malloc(sizeof(char) * s1_len + 1);
	if (mem != NULL)
	{
		ft_memcpy(mem, s1, s1_len);
		mem[s1_len] = '\0';
	}
	return (mem);
}

static int	is_sep(char s, char c)
{
	if (s == c || s == 0)
		return (1);
	return (0);
}

static int	count_size(char const *s, char c)
{
	int	s_size;

	s_size = 0;
	while (*s)
	{
		if (!is_sep(*s, c) && is_sep(*(s + 1), c))
			s_size++;
		s++;
	}
	return (s_size);
}

static void	ft_freeall(char **spl)
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

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;

	if (len >= ft_strlen(s))
		len = ft_strlen(s);
	if (ft_strlen(s) < start)
		return (ft_strdup(""));
	if (ft_strlen(s) - start < len)
		substr = (char *)malloc(sizeof(char) * (ft_strlen(s) - start) + 1);
	else
		substr = (char *)malloc(sizeof(char) * (len + 1));
	if (!substr)
		return (NULL);
	ft_strlcpy(substr, (char *)(s + start), len + 1);
	return (substr);
}

static void	place_word(char **spl, char const *s, char c, int *flag)
{
	int		s_idx;
	int		i;

	s_idx = 0;
	while (*s)
	{
		if (is_sep(*s, c))
			s++;
		else
		{
			i = 0;
			while (*(s + i) && !is_sep(*(s + i), c))
				i++;
			spl[s_idx] = ft_substr(s, 0, i);
			if (spl[s_idx] == NULL)
			{
				*flag = 1;
				ft_freeall(spl);
				return ;
			}
			s_idx += 1;
			s += i;
		}
	}
}

char	**ft_split(char const *s, char c)
{
	char	**spl;
	int		s_size;
	int		flag;

	flag = 0;
	if (!s)
		return (NULL);
	s_size = count_size(s, c);
	spl = (char **) malloc(sizeof(char *) * (s_size + 1));
	if (spl == NULL)
		return (NULL);
	place_word(spl, s, c, &flag);
	if (flag == 1)
		return (NULL);
	spl[s_size] = NULL;
	return (spl);
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

void	my_qsort(int *arr, int left, int right)
{
	int		l;
	int		r;
	int		mid;
	int		tmp;

	if (left >= right)
		return ;
	l = left - 1;
	r = right + 1;
	mid = arr[(l + r) / 2];
	while (1)
	{
		while (arr[++l] < mid)
			;
		while (arr[--r] > mid)
			;
		if (l >= r)
			break ;
		tmp = arr[l];
		arr[l] = arr[r];
		arr[r] = tmp;
	}
	my_qsort(arr, left, l - 1);
	my_qsort(arr, r + 1, right);
}

void	dup_check(int *arr, int n)
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
			write(1, "Error\n", 6);
			exit(0);
		}
	}
	free(tmp_arr);
}

int	front_idx(t_deque *d, int idx)
{
	int	i;

	i = d->head;
	while (idx--)
	{
		i++;
		if (i == d->capacity)
			i = 0;
	}
	return (d->arr[i]);
}

void	print_cmd_sub(int op)
{
	if (op == g_sa)
		write(1, "sa\n", 3);
	else if (op == g_sb)
		write(1, "sb\n", 3);
	else if (op == g_ra)
		write(1, "ra\n", 3);
	else if (op == g_rb)
		write(1, "rb\n", 3);
	else if (op == g_rra)
		write(1, "rra\n", 4);
	else if (op == g_rrb)
		write(1, "rrb\n", 4);
	else if (op == g_pa)
		write(1, "pa\n", 3);
	else if (op == g_pb)
		write(1, "pb\n", 3);
	else if (op == g_rr)
		write(1, "rr\n", 3);
	else if (op == g_rrr)
		write(1, "rrr\n", 4);
	else if (op == g_ss)
		write(1, "ss\n", 3);
}

void	merge_cmd(t_deque *cmd, t_deque *cmd2);

void	merge_cmd_sub4(t_deque *cmd, t_deque *cmd2, int a, int b)
{
	if ((a == g_rrr && b == g_ra) || (a == g_ra && b == g_rrr))
	{
		pop_back(cmd2);
		pop_front(cmd);
		push_back(cmd2, g_rrb);
		if (!empty(cmd) && !empty(cmd2))
			merge_cmd(cmd, cmd2);
	}
	else if ((a == g_rrr && b == g_rb) || (a == g_rb && b == g_rrr))
	{
		pop_back(cmd2);
		pop_front(cmd);
		push_back(cmd2, g_rra);
		if (!empty(cmd) && !empty(cmd2))
			merge_cmd(cmd, cmd2);
	}
	else if ((a == g_rr && b == g_rrr) || (a == g_rrr && b == g_rr))
	{
		pop_back(cmd2);
		pop_front(cmd);
		if (!empty(cmd) && !empty(cmd2))
			merge_cmd(cmd, cmd2);
	}
}

void	merge_cmd_sub3(t_deque *cmd, t_deque *cmd2, int a, int b)
{
	if ((a == g_rr && b == g_rra) || (a == g_rra && b == g_rr))
	{
		pop_back(cmd2);
		pop_front(cmd);
		push_back(cmd2, g_rb);
		if (!empty(cmd) && !empty(cmd2))
			merge_cmd(cmd, cmd2);
	}
	else if ((a == g_rr && b == g_rrb) || (a == g_rrb && b == g_rr))
	{
		pop_back(cmd2);
		pop_front(cmd);
		push_back(cmd2, g_ra);
		if (!empty(cmd) && !empty(cmd2))
			merge_cmd(cmd, cmd2);
	}
	else if ((a == g_rb && b == g_rrb) || (a == g_rrb && b == g_rb))
	{
		pop_back(cmd2);
		pop_front(cmd);
		if (!empty(cmd) && !empty(cmd2))
			merge_cmd(cmd, cmd2);
	}
	else
		merge_cmd_sub4(cmd, cmd2, a, b);
}

void	merge_cmd_sub2(t_deque *cmd, t_deque *cmd2, int a, int b)
{
	if ((a == g_ra && b == g_rb) || (a == g_rb && b == g_ra))
	{
		pop_back(cmd2);
		pop_front(cmd);
		push_back(cmd2, g_rr);
		if (!empty(cmd) && !empty(cmd2))
			merge_cmd(cmd, cmd2);
	}
	else if ((a == g_rra && b == g_rrb) || (a == g_rrb && b == g_rra))
	{
		pop_back(cmd2);
		pop_front(cmd);
		push_back(cmd2, g_rrr);
		if (!empty(cmd) && !empty(cmd2))
			merge_cmd(cmd, cmd2);
	}
	else if ((a == g_ra && b == g_rra) || (a == g_rra && b == g_ra))
	{
		pop_back(cmd2);
		pop_front(cmd);
		if (!empty(cmd) && !empty(cmd2))
			merge_cmd(cmd, cmd2);
	}
	else
		merge_cmd_sub3(cmd, cmd2, a, b);
}

void	merge_cmd_sub1(t_deque *cmd, t_deque *cmd2, int a, int b)
{
	if ((a == g_sb && b == g_ss) || (a == g_ss && b == g_sb))
	{
		pop_back(cmd2);
		pop_front(cmd);
		push_back(cmd2, g_sa);
		if (!empty(cmd) && !empty(cmd2))
			merge_cmd(cmd, cmd2);
	}
	else if ((a == g_sb && b == g_sa) || (a == g_sa && b == g_sb))
	{
		pop_back(cmd2);
		pop_front(cmd);
		push_back(cmd2, g_ss);
		if (!empty(cmd) && !empty(cmd2))
			merge_cmd(cmd, cmd2);
	}
	else if ((a == g_pa && b == g_pb) || (a == g_pb && b == g_pa))
	{
		pop_back(cmd2);
		pop_front(cmd);
		if (!empty(cmd) && !empty(cmd2))
			merge_cmd(cmd, cmd2);
	}
	else
		merge_cmd_sub2(cmd, cmd2, a, b);
}

void	merge_cmd(t_deque *cmd, t_deque *cmd2)
{
	int		a;
	int		b;

	a = back(cmd2);
	b = front(cmd);
	if ((a == g_sa && b == g_sa) || (a == g_sb && b == g_sb))
	{
		pop_back(cmd2);
		pop_front(cmd);
		if (!empty(cmd) && !empty(cmd2))
			merge_cmd(cmd, cmd2);
	}
	else if ((a == g_sa && b == g_ss) || (a == g_ss && b == g_sa))
	{
		pop_back(cmd2);
		pop_front(cmd);
		push_back(cmd2, g_sb);
		if (!empty(cmd) && !empty(cmd2))
			merge_cmd(cmd, cmd2);
	}
	else
		merge_cmd_sub1(cmd, cmd2, a, b);
}

void	print_cmd(t_deque *cmd)
{
	int		idx;
	int		i;
	t_deque	*cmd2;

	cmd2 = make_deque();
	idx = cmd->head;
	while (!empty(cmd))
	{
		push_back(cmd2, pop_front(cmd));
		if (!empty(cmd) && !empty(cmd2))
		{
			merge_cmd(cmd, cmd2);
		}
	}
	idx = cmd2->head;
	i = -1;
	while (++i < cmd2->size)
	{
		print_cmd_sub(cmd2->arr[idx++]);
		if (idx == cmd2->capacity)
			idx = 0;
	}
	free(cmd2);
}

void	do_rra(t_deque *a, t_deque *cmd)
{
	push_back(cmd, g_rra);
	reverse_rotate(a);
}

void	do_rrb(t_deque *b, t_deque *cmd)
{
	push_back(cmd, g_rrb);
	reverse_rotate(b);
}

void	do_rrr(t_deque *a, t_deque *b, t_deque *cmd)
{
	push_back(cmd, g_rrr);
	reverse_rotate(a);
	reverse_rotate(b);
}

void	do_ra(t_deque *a, t_deque *cmd)
{
	push_back(cmd, g_ra);
	rotate(a);
}

void	do_rb(t_deque *b, t_deque *cmd)
{
	push_back(cmd, g_rb);
	rotate(b);
}

void	do_sa(t_deque *a, t_deque *cmd)
{
	push_back(cmd, g_sa);
	swap_top(a);
}

void	do_sb(t_deque *b, t_deque *cmd)
{
	push_back(cmd, g_sb);
	swap_top(b);
}

void	do_pb(t_deque *a, t_deque *b, t_deque *cmd)
{
	push_back(cmd, g_pb);
	push(a, b);
}

void	do_pa(t_deque *a, t_deque *b, t_deque *cmd)
{
	push_back(cmd, g_pa);
	push(b, a);
}

void	deque_to_arr(t_deque *d, int *a)
{
	int		i;

	i = -1;
	while (++i < d->size)
		a[i] = front_idx(d, i);
}

typedef struct s_pair
{
	int		first;
	int		second;
}				t_pair;

t_pair	find_pivot(t_deque *d, int n)
{
	t_pair	ret;
	int		*arr;
	int		i;
	int		idx;

	arr = (int *) malloc(sizeof(int) * n);
	i = -1;
	idx = d->head;
	while (++i < n)
	{
		arr[i] = d->arr[idx++];
		if (idx == d->capacity)
			idx = 0;
	}
	my_qsort(arr, 0, n - 1);
	ret.first = arr[n - (n / 3 + (n % 3 != 0)) * 2];
	ret.second = arr[n - (n / 3 + (n % 3 != 0))];
	free(arr);
	return (ret);
}

t_pair	find_pivot_b_to_a(t_deque *d, int n)
{
	t_pair	ret;
	int		*arr;
	int		i;
	int		idx;

	arr = (int *) malloc(sizeof(int) * n);
	i = -1;
	idx = d->head;
	while (++i < n)
	{
		arr[i] = d->arr[idx++];
		if (idx == d->capacity)
			idx = 0;
	}
	my_qsort(arr, 0, n - 1);
	ret.first = arr[n / 3 + (n % 3 != 0) - 1];
	ret.second = arr[(n / 3 + (n % 3 != 0)) * 2 - 1];
	free(arr);
	return (ret);
}

void	a_to_b(t_deque *a, t_deque *b, t_deque *cmd, int n);
void	b_to_a(t_deque *a, t_deque *b, t_deque *cmd, int n);

void	a_to_b_sub1(t_deque *a, t_deque *cmd, int n)
{
	if (n == 2)
		if (front_idx(a, 0) > front_idx(a, 1))
			do_sa(a, cmd);
}

void	a_to_b_sub2(t_deque *a, t_deque *b, t_deque *cmd, int n)
{
	a_to_b(a, b, cmd, n / 3 + (n % 3 != 0));
	b_to_a(a, b, cmd, n / 3 + (n % 3 != 0));
	b_to_a(a, b, cmd, n - (n / 3 + (n % 3 != 0)) * 2);
}

void	b_to_a_sub1(t_deque *a, t_deque *b, t_deque *cmd, int n)
{
	if (n == 2)
		if (front_idx(b, 0) < front_idx(b, 1))
			do_sb(b, cmd);
	while (n--)
		do_pa(a, b, cmd);
}

void	b_to_a_sub2(t_deque *a, t_deque *b, t_deque *cmd, int n)
{
	a_to_b(a, b, cmd, n / 3 + (n % 3 != 0));
	b_to_a(a, b, cmd, n / 3 + (n % 3 != 0));
}

void	a_to_b(t_deque *a, t_deque *b, t_deque *cmd, int n)
{
	int		i;
	t_pair	pivot;

	if (n < 3)
	{
		a_to_b_sub1(a, cmd, n);
		return ;
	}
	pivot = find_pivot(a, n);
	i = -1;
	while (++i < n)
	{
		if (front(a) >= pivot.second)
			do_ra(a, cmd);
		else
		{
			do_pb(a, b, cmd);
			if (front(b) >= pivot.first)
				do_rb(b, cmd);
		}
	}
	i = -1;
	while (++i < (n / 3 + (n % 3 != 0)))
		do_rrr(a, b, cmd);
	a_to_b_sub2(a, b, cmd, n);
}

void	b_to_a(t_deque *a, t_deque *b, t_deque *cmd, int n)
{
	int		i;
	t_pair	pivot;

	if (n < 3)
	{
		b_to_a_sub1(a, b, cmd, n);
		return ;
	}
	pivot = find_pivot_b_to_a(b, n);
	i = -2 - n;
	while (++i < -1)
	{
		if (front(b) <= pivot.first)
			do_rb(b, cmd);
		else
		{
			do_pa(a, b, cmd);
			if (front(a) <= pivot.second)
				do_ra(a, cmd);
		}
	}
	a_to_b(a, b, cmd, n - (n / 3 + (n % 3 != 0)) * 2);
	while (++i < (n / 3 + (n % 3 != 0)))
		do_rrr(a, b, cmd);
	b_to_a_sub2(a, b, cmd, n);
}

void	do_3(t_deque *d, t_deque *cmd)
{
	int		a[3];

	deque_to_arr(d, a);
	if (a[0] > a[1])
	{
		if (a[0] > a[2])
		{
			do_ra(d, cmd);
			if (a[1] > a[2])
				do_sa(d, cmd);
		}
		else
			do_sa(d, cmd);
	}
	else
	{
		if (a[1] > a[2])
		{
			do_rra(d, cmd);
			if (a[2] > a[0])
				do_sa(d, cmd);
		}
	}
}

int	is_sorted(t_deque *a)
{
	int		i;
	int		cur;
	int		val;

	cur = a->head;
	val = a->arr[cur];
	i = a->size;
	if (!i)
		return (1);
	while (--i)
	{
		cur++;
		if (cur == a->capacity)
			cur = 0;
		if (val > a->arr[cur])
			return (0);
		val = a->arr[cur];
	}
	return (1);
}

void	do_4(t_deque *a, t_deque *b, t_deque *cmd)
{
	int		i;
	int		arr[4];
	int		min_idx;

	deque_to_arr(a, arr);
	min_idx = 0;
	i = -1;
	while (++i < 4)
		if (arr[min_idx] > arr[i])
			min_idx = i;
	while (min_idx--)
		do_ra(a, cmd);
	if (!is_sorted(a))
	{
		do_pb(a, b, cmd);
		do_3(a, cmd);
		do_pa(a, b, cmd);
	}
}

void	do_5_sub(t_deque *a, t_deque *b, int *arr, t_deque *cmd)
{
	int		i;

	my_qsort(arr, 0, 4);
	i = 2;
	while (i)
	{
		if (front_idx(a, 0) < arr[2])
		{
			do_pb(a, b, cmd);
			i--;
		}
		else
			do_ra(a, cmd);
	}
}

void	do_5(t_deque *a, t_deque *b, t_deque *cmd)
{
	int		arr[5];

	if (is_sorted(a))
		return ;
	deque_to_arr(a, arr);
	do_5_sub(a, b, arr, cmd);
	if (!is_sorted(a))
		do_3(a, cmd);
	if (front_idx(b, 0) < front_idx(b, 1))
		do_sb(b, cmd);
	do_pa(a, b, cmd);
	do_pa(a, b, cmd);
}

void	do_2(t_deque *a, t_deque *cmd)
{
	if (front_idx(a, 0) > front_idx(a, 1))
		do_sa(a, cmd);
}

t_deque	*do_sort(int *arr, int n)
{
	t_deque	*a;
	t_deque	*b;
	t_deque	*cmd;
	int		i;

	a = make_deque();
	b = make_deque();
	cmd = make_deque();
	i = -1;
	while (++i < n)
		push_back(a, arr[i]);
	if (n == 2)
		do_2(a, cmd);
	else if (n == 3)
		do_3(a, cmd);
	else if (n == 4)
		do_4(a, b, cmd);
	else if (n == 5)
		do_5(a, b, cmd);
	else
		a_to_b(a, b, cmd, n);
	free(a);
	free(b);
	return (cmd);
}

int	main(int argc, char **argv)
{
	int			n;
	int			i;
	int			*arr;
	int			idx;
	t_deque		*cmd;

	i = 0;
	n = 0;
	while (++i < argc)
		split_space(argv[i], &n);
	i = 0;
	idx = 0;
	arr = (int *) malloc(sizeof(int) * n);
	while (++i < argc)
		append_num(argv[i], arr, &idx);
	dup_check(arr, n);
	cmd = do_sort(arr, n);
	print_cmd(cmd);
	free(arr);
	free(cmd);
	return (0);
}
