/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_tokenize2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark < gyopark@student.42seoul.kr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 14:33:41 by gyopark           #+#    #+#             */
/*   Updated: 2023/02/19 17:07:01 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*copy_token(t_token *cur)
{
	t_token	*temp;

	temp = make_token();
	temp->cmds = cur->cmds;
	temp->null_flag = cur->null_flag;
	temp->next = cur->next;
	temp->prev = cur->prev;
	temp->str = ft_strdup(cur->str);
	temp->type = cur->type;
	return (temp);
}

void	get_rid_null_node(t_token **cur)
{
	t_token	*tmp;
	t_token	*nxt;

	tmp = (*cur);
	nxt = NULL;
	while (tmp)
	{
		if (tmp->next)
		{
			if (tmp->next->null_flag == 1)
			{
				nxt = tmp->next;
				tmp->next = nxt->next;
				tmp = tmp->next;
				free(nxt->str);
				free(nxt);
				nxt = NULL;
			}
			else
				tmp = tmp->next;
		}
		else
			break ;
	}
}

// t_token	*get_rid_null_node(t_token *cur)
// {
// 	t_token	*new_cur;
// 	t_token	*temp;

// 	new_cur = make_token();
// 	cur = cur->next;
// 	while (cur)
// 	{
// 		if (cur->null_flag == 0)
// 		{
// 			temp = copy_token(cur);
// 			new_cur->next = temp;
// 			temp->prev = new_cur;
// 			new_cur = new_cur->next;
// 		}
// 		cur = cur->next;
// 	}
// 	while (new_cur->prev)
// 		new_cur = new_cur->prev;
// 	if (new_cur->next == NULL)
// 	{
// 		free(new_cur);
// 		return (NULL);
// 	}
// 	return (new_cur);
// }
