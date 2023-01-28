/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_tokenize.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 14:14:14 by gyopark           #+#    #+#             */
/*   Updated: 2023/01/28 18:44:17 by gyopark          ###   ########.fr       */
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

t_token	*tokenize(char *s, char **envp)
{
	t_token	*cur;
	t_str	*buf;

	cur = make_token();
	buf = make_str();
	while (*s != '\n' && *s)
	{
		if (*s == '<' || *s == '>' || *s == '|')
			cur = read_pipe_redir(&s, cur, buf);
		else if (is_space(*s))
			s++;
		else
			cur = read_word(&s, cur, buf, envp);
	}
	while (cur->prev)
		cur = cur->prev;
	return (cur);
}

int	main(__attribute__((unused))int argc,
		__attribute__((unused))char **argv, char **envp)
{
	char	*cmd;
	t_token	*t;

	while (1)
	{
		cmd = readline("inp> ");
		if (!cmd || ft_strncmp(cmd, "EOF\n", ft_strlen(cmd)) == 0)
			break ;
		t = tokenize(cmd, envp);
		print_token(t->next);
		free(cmd);
		free(t);
	}
	/** char	*line; */
	/** t_token	*test; */
    /**  */
	/** line = "$HOME | $home2"; */
	/** test = tokenize(line); */
	/** print_token(test->next); */
	/** free(test); */
	return (0);
}
