/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark < gyopark@student.42seoul.kr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 20:17:04 by gyopark           #+#    #+#             */
/*   Updated: 2023/02/14 20:23:48 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		if (value)
			printf("%s=%s\n", key, value);
		temp = temp->next;
	}
}

int	built_env(char **builtin, t_list *head)
{
	if (builtin[1])
		return (0);
	print_env(head);
	g_exit_code = 0;
	return (1);
}
