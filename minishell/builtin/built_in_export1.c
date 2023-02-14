/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_export1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark < gyopark@student.42seoul.kr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 20:19:39 by gyopark           #+#    #+#             */
/*   Updated: 2023/02/14 20:25:42 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	env_error_check(char *key)
{
	char	*temp;
	int		i;

	if (!(key))
		return (1);
	i = 0;
	if (key && key[0] == '=')
		return (1);
	while (temp[i] && temp[i] != '=')
	{
		if (ft_isalpha(temp[i]) || temp[i] == '_')
			;
		else
			return (1);
		i++;
	}
	return (0);
}

void	init_export_parsing(int *ret, char **t)
{
	*ret = 0;
	t++;
}

int	export_parsing(t_list **head, char **t)
{
	int	ret;

	init_export_parsing(&ret, t);
	while (*t)
	{
		if (env_error_check(*t))
		{
			printf("export: `%s': not a valid identifier\n", *t);
			t++;
			ret = 1;
			continue ;
		}
		while (*t && **t)
		{
			if (*t[0] == '=')
			{
				t++;
				ret = 1;
				continue ;
			}
			make_env(*t, head);
			t++;
		}
	}
	return (ret);
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

int	built_export(char **builtin, t_list *head)
{
	char	**t;

	(void)builtin;
	if (!t)
		return (0);
	if (!builtin[1])
	{
		print_export(head);
		g_exit_code = 0;
		return (1);
	}
	else
	{
		if (!export_parsing(&head, builtin))
			g_exit_code = 0;
		else
			g_exit_code = 1;
	}
	return (1);
}
