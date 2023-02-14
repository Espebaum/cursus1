/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_export2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark < gyopark@student.42seoul.kr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 20:25:59 by gyopark           #+#    #+#             */
/*   Updated: 2023/02/14 20:32:39 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	del_one(char *t, t_list *head_first)
{
	t_list	*head;
	t_list	*prev;

	head = head_first;
	prev = 0;
	while (head)
	{
		if (!ft_strncmp(head->key, t, ft_strlen(t) + 1))
		{
			if (prev)
				prev->next = head->next;
			else
				head_first = head_first->next;
			free(head->key);
			if (head->value)
				free(head->value);
			free(head);
			break ;
		}
		prev = head;
		head = head->next;
	}
}

void	new_value(t_list **head, char *key, char *value)
{
	t_list	*temp;

	temp = *head;
	while (temp)
	{
		if (!strncmp(temp->key, key, ft_strlen(temp->key) + 1))
		{
			if (value)
			{
				if (temp->value)
					free(temp->value);
				temp->value = value;
			}
			return ;
		}
		temp = temp->next;
	}
	ft_lstadd_back(head, ft_lstnew(key, value));
}

void	init_make_env(int *i, char **key, char **value, char *t)
{
	int	len;

	len = ft_strlen(t);
	*i = 0;
	*key = (char *)malloc(sizeof(char) * (len + 1));
	if (ft_strchr(t, '='))
	{
		*value = (char *)malloc(sizeof(char) * (len + 1));
		*value[0] = 0;
	}
	else
		*value = 0;
	*key[0] = 0;
}

void	make_env(char *t, t_list **head)
{
	int		flag;
	char	*key;
	char	*value;
	int		i;

	flag = 0;
	init_make_env(&i, &key, &value, t);
	while (t && *t)
	{
		if (*t == '=' && flag == 0)
		{
			t++;
			i = 0;
			flag = 1;
			continue ;
		}
		else if (*t != '=' && flag == 0)
			key[i++] = *t;
		else if (flag == 1)
			value[i++] = *t;
		t++;
	}
	new_value(head, key, value);
}
