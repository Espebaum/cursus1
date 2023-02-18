/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark < gyopark@student.42seoul.kr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 15:52:55 by gyopark           #+#    #+#             */
/*   Updated: 2023/02/18 21:56:31 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	resize_str(t_str *str)
{
	char	*tmp;
	int		i;

	tmp = (char *) malloc(sizeof(char) * str->capacity * 2);
	i = -1;
	while (++i < str->len)
		tmp[i] = str->s[i];
	free(str->s);
	str->s = tmp;
	str->capacity *= 2;
}

void	free_str(t_str *str)
{
	free(str->s);
	free(str);
	str = 0;
}

void	clear_str(t_str *str)
{
	free(str->s);
	str->s = (char *) malloc(sizeof(char) * str->capacity);
	str->len = 0;
	str->s[0] = '\0';
}

void	free_token(t_token *cur)
{
	t_token	*nxt;

	if (cur->str == NULL && cur->next == NULL)
	{
		free(cur);
		return ;
	}
	while (cur)
	{
		if (cur->str)
			free(cur->str);
		nxt = cur->next;
		free(cur);
		cur = nxt;
	}
}

void	print_token(t_token *cur)
{
	while (cur)
	{
		printf("\n");
		if (cur->type == 1)
			printf("%s\n", "TYPE  : REDIRECTION");
		else if (cur->type == 2)
			printf("%s\n", "TYPE  : WORD");
		else if (cur->type == 3)
			printf("%s\n", "TYPE  : PIPE");
		printf("NULL FLAG : %d\n", cur->null_flag);
		printf("VALUE : %s\n", cur->str);
		printf("\n");
		cur = cur->next;
	}
}
