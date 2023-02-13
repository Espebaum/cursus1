/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark < gyopark@student.42seoul.kr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 22:56:35 by youngski          #+#    #+#             */
/*   Updated: 2023/02/13 19:07:41 by gyopark          ###   ########.fr       */
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

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*temp;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	temp = ft_lstlast(*lst);
	temp->next = new;
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
		t++;
	}
	return (*head);
}

int	env_error_check(char *key)
{
	char	*temp;
	int		i;

	if (!(key))
		return (1);
	i = 0;
	temp = (char *)key;
	while (temp[i])
	{
		if (ft_isalpha(temp[i]) || temp[i] == '_' || temp[i] == '=')
		{
			return (0);
		}
		i++;
	}
	return (1);
}

void	new_value(t_list **head, char *key, char *value)
{
	//중복체크
	t_list	*temp;

	temp = *head;
	while (temp)
	{
		if (!strncmp(temp->key, key, ft_strlen(temp->key) + 1))
		{
			temp->value = value;
			return ;
		}
		temp = temp->next;
	}
	ft_lstadd_back(head, ft_lstnew(key, value));
}

char	**make_envp_arr(t_list *head)
{
	int		i;
	char	*t;
	char	**ret;
	t_list	*temp;

	i = 0;
	temp = head;
	while (temp)
	{
		i++;
		temp = temp->next;
	}
	ret = (char **)malloc(sizeof(char *) * i + 1);
	ret[i] = 0;
	i = 0;
	while (head)
	{
		t = ft_strjoin(head->key, "=");
		t = ft_strjoin(t, head->value);

		ret[i++] = t;
		head = head->next;
	}
	return (ret);
}

void	print_env(t_list *head)
{
	t_list	*temp;
	char	*key;
	char	*value;

	temp = head;
	while (temp)
	{
		key = temp->key;
		value = temp->value;
		// if (value == 0)
		// {
		// 	temp = temp->next;
		// 	printf("skip a!!!!\n\n");
		// 	continue ;
		// }
		//else
			printf("%s=%s\n", key, value);
		temp = temp->next;
	}

}

void	print_export(t_list *head)
{
	t_list	*temp;
	char	*key;
	char	*value;

	temp = head;
	while (temp)
	{
		key = temp->key;
		value = temp->value;
		if (value == 0)
			printf("declar -x %s\n", key);
		else
			printf("declar -x %s=\"%s\"\n", key, value);
		temp = temp->next;
	}
}

/*
//메인에서 반복문안에서 init_env_list, make_envp_arr 를 계속해준다.
int	main(int argc, char **argv, char **env)
{
	t_list	*head;

	head = init_env_list(env, &head);
	new_value(&head, argv[1], argv[2]);
	make_envp_arr(head, &env);
	print_env(head);
}
*/
