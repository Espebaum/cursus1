/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_tokenize.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 14:14:14 by gyopark           #+#    #+#             */
/*   Updated: 2023/01/30 17:41:41 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_word_end(char s)
{
	if (s == '|' || s == ' ' || s == '\n' || s == 0 || s == '<' || s == '>')
		return (1);
	return (0);
}

int	is_line_end(char s)
{
	if (s == '\n' || s == '\0')
		return (1);
	return (0);
}

char	**deep_copy_env(char **envp)
{
	int		i;
	int		j;
	char	**cp_envp;

	i = -1;
	j = 0;
	while (envp[++i])
		;
	cp_envp = (char **)malloc(sizeof(char *) * (i + 1));
	while (j < i)
	{
		cp_envp[j] = ft_strdup(envp[j]);
		j++;
	}
	cp_envp[j] = NULL;
	return (cp_envp);
}

t_token	*tokenize(char *s, char **envp, int *count)
{
	t_token	*cur;
	t_str	*buf;

	cur = make_token();
	buf = make_str();
	while (*s != '\n' && *s)
	{
		if (*s == '<' || *s == '>' || *s == '|')
			cur = read_pipe_redir(&s, cur, buf, count);
		else if (is_char_space(*s))
			s++;
		else
			cur = read_word(&s, cur, buf, envp);
	}
	while (cur->prev)
		cur = cur->prev;
	return (cur);
}

t_token	*go_tokenize(char *cmd, char **envp, int *count, t_token *t)
{
	char	**temp;

	temp = deep_copy_env(envp);
	t = tokenize(cmd, temp, count);
	print_token(t->next);
	free(temp);
	return (t);
}
