/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_tokenize.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark < gyopark@student.42seoul.kr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 14:14:14 by gyopark           #+#    #+#             */
/*   Updated: 2023/02/17 17:16:48 by gyopark          ###   ########.fr       */
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

void	free_spl(char **temp)
{
	int	i;

	i = -1;
	while (temp && temp[++i])
	{
		free(temp[i]);
		temp[i] = NULL;
		if (temp[i + 1] == NULL)
			break ;
	}
	free(temp);
	temp = NULL;
}

t_token	*tokenize(char *s, char **envp)
{
	t_token	*new_cur;
	t_token	*cur;
	t_str	*buf;
	char	**temp;
	int		flag;

	flag = 0;
	cur = make_token();
	buf = make_str();
	while (*s != '\n' && *s)
	{
		if (*s == '<' || *s == '>' || *s == '|')
			cur = read_pipe_redir(&s, cur, buf);
		else if (is_char_space(*s))
			s++;
		else
		{
			temp = deep_copy_env(envp);
			cur = read_word(&s, cur, buf, temp);
		}
	}
	free_str(buf);
	while (cur->prev)
		cur = cur->prev;
	new_cur = get_rid_null_node(cur);
	free_token(cur);
	return (new_cur);
}

t_token	*go_tokenize(char *cmd, char **envp, t_token *t)
{
	t = tokenize(cmd, envp);
	print_token(t->next);
	return (t);
}
