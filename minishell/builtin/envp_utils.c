/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark < gyopark@student.42seoul.kr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 22:56:35 by youngski          #+#    #+#             */
/*   Updated: 2023/02/16 21:29:27 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (0);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back(t_list **lst, t_list *newlst)
{
	t_list	*temp;

	if (*lst == NULL)
	{
		*lst = newlst;
		return ;
	}
	temp = ft_lstlast(*lst);
	temp->next = newlst;
}

t_list	*ft_lstnew(void *key, void *value)
{
	t_list	*newlist;

	newlist = (t_list *)malloc(sizeof(t_list));
	if (!newlist)
		return (0);
	newlist->key = key;
	newlist->value = value;
	newlist->next = NULL;
	return (newlist);
}

t_list	*init_env_list(char **env, t_list **head)
{
	char	**t;
	char	**str;
	t_list	*temp;

	t = env;
	while (t)
	{
		str = ft_split(*t, '=');
		if (str == 0)
			break ;
		temp = ft_lstnew(str[0], str[1]);
		ft_lstadd_back(head, temp);
		free(str);
		t++;
	}
	return (*head);
}

char	**make_envp_arr(t_list *head)
{
	int		i;
	char	*t;
	char	*t_fr;
	char	**ret;
	t_list	*temp;

	i = 0;
	temp = head;
	while (temp->next)
	{
		i++;
		temp = temp->next;
	}
	ret = (char **)malloc(sizeof(char *) * (i + 1));
	ret[i] = 0;
	i = 0;
	while (head->next)
	{
		t = ft_strjoin(head->key, "=");
		t_fr = t;
		t = ft_strjoin(t, head->value);
		free(t_fr);
		ret[i++] = t;
		head = head->next;
	}
	return (ret);
}
