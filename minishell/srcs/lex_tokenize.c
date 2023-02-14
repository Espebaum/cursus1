/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_tokenize.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark < gyopark@student.42seoul.kr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 14:14:14 by gyopark           #+#    #+#             */
/*   Updated: 2023/02/14 13:15:07 by youngski         ###   ########.fr       */
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

t_token	*tokenize(char *s, char **envp)
{
	t_token	*cur;
	t_str	*buf;
	char	**temp;
	int		flag;

	flag = 0;
	cur = make_token();
	buf = make_str();
	while (*s != '\n' && *s)
	{
		temp = deep_copy_env(envp);
		if (*s == '<' || *s == '>' || *s == '|')
			cur = read_pipe_redir(&s, cur, buf);
		else if (is_char_space(*s))
			s++;
		else
			cur = read_word(&s, cur, buf, temp);
	}
	while (cur->prev)
		cur = cur->prev;
	free(temp);
	return (cur);
}

t_token	*go_tokenize(char *cmd, char **envp, t_token *t)
{
	t = tokenize(cmd, envp);
	print_token(t->next);
	return (t);
}
