/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 17:01:33 by gyopark           #+#    #+#             */
/*   Updated: 2022/11/15 17:08:17 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;
	t_list	*curr;

	curr = *lst;
	if (!lst || !del)
		return ;
	while (curr)
	{
		tmp = curr->next;
		ft_lstdelone(curr, del);
		curr = tmp;
	}
	*lst = NULL;
}
