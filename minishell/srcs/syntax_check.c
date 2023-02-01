/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 19:57:00 by gyopark           #+#    #+#             */
/*   Updated: 2023/02/01 22:23:02 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	rule_pipe(int *type_arr, int len)
{
	int		i;

	if (type_arr[0] == 2 || type_arr[len - 1] == 2)
		return (-1);
	i = 0;
	if (len > 2)
		while (++i < len - 1)
			if ((type_arr[i] == 2)
				&& (type_arr[i - 1] != 1 || type_arr[i + 1] != 1))
				return (-1);
	return (0);
}

int	rule_redirection(int *type_arr, int len)
{
	int		i;

	if ((len == 1 && type_arr[0] == 0) || type_arr[len - 1] == 0)
		return (-1);
	i = -1;
	if (len > 1)
		while (++i < len - 1)
			if (type_arr[i] == 0 && type_arr[i + 1] != 1)
				return (-1);
	return (0);
}

int	check_rules(int *type_arr, int len)
{
	int		ret;

	ret = 0;
	ret = rule_pipe(type_arr, len);
	if (ret == -1)
		return (ret);
	ret = rule_redirection(type_arr, len);
	if (ret == -1)
		return (ret);
	return (ret);
}

int	*make_type_arr(t_token *head, int *token_len)
{
	t_token	*temp;
	int		idx;
	int		*type_arr;

	idx = -1;
	*token_len = -1;
	temp = head;
	while (temp)
	{
		(*token_len)++;
		temp = temp->next;
	}
	temp = head->next;
	type_arr = (int *) malloc(sizeof(int) * (*token_len));
	while (++idx < *token_len)
	{
		type_arr[idx] = temp->type;
		temp = temp->next;
	}
	return (type_arr);
}

int	check_syntax(t_token *head)
{
	int		token_len;
	int		*type_arr;

	token_len = 0;
	type_arr = make_type_arr(head, &token_len);
	if (check_rules(type_arr, token_len) == -1)
	{
		ft_putendl_fd("syntax error", 2);
		return (-1);
	}
	return (0);
}
