/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_read.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 17:22:29 by gyopark           #+#    #+#             */
/*   Updated: 2023/02/04 22:23:08 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	read_env(char **s, t_str *buf, char **envp, int *env_flag)
{
	t_str	*env;
	int		i;
	int		env_num;

	i = 0;
	env = make_str();
	while (!is_word_end(*(++(*s))) && **s != '\"')
	{
		if (**s == '$') //
			break ;		//
		push_str(env, **s);
	}
	while (envp[i])
	{
		env_num = get_env_num(envp[i]);
		if (ft_strncmp(env->s, envp[i], env_num) == 0)
		{
			envp[i] += env_num + 1;
			while (*(envp[i])++)
				push_str(buf, *envp[i]);
			break ;
		}
		i++;
	}
	if ((buf->s[0]) == '\0')
		push_str(buf, '\n');
	(*env_flag)++;
	free_str(env);
}

int	read_word_squote(char **s, t_str *buf)
{
	(*s)++;
	while (!is_line_end(**s) && **s != '\'')
		push_str(buf, *((*s)++));
	if (**s != '\'')
		return (1);
	(*s)++;
	printf("in squote: [%s]\n", buf->s);
	return (0);
}

int	read_word_dquote(char **s, t_str *buf, char **envp)
{
	int		env_flag;
	char	**temp;

	(*s)++;
	//env_flag = 0;
	while (!is_line_end(**s) && **s != '\"')
	{
		temp = deep_copy_env(envp);
		//if (env_flag == 1)
		//	break ;
		if (**s == '$')
			read_dquote_env(s, buf, temp, &env_flag);
		else
			push_str(buf, *((*s)++));
	}
	if (**s != '\"')
		return (1);
	(*s)++;
	printf("in dquote: [%s]\n", buf->s);
	return (0);
}

t_token	*read_word(char **s, t_token *cur, t_str *buf, char **envp)
{
	int		is_fail;
	int		env_flag;

	is_fail = 0;
	env_flag = 0;
	while (!is_word_end(**s))
	{
		if (env_flag == 1)
			break ;
		if (**s == '$' && env_flag == 0)
			read_env(s, buf, envp, &env_flag);
		else if (**s == '\'')
			is_fail |= read_word_squote(s, buf);
		else if (**s == '\"')
			is_fail |= read_word_dquote(s, buf, envp);
		else
			push_str(buf, *((*s)++));
	}
	if (is_fail)
		cur = push_token(T_ERROR, buf, cur);
	else
	{
		cur = push_token(T_WORD, buf, cur);
		if (cur->flag == 1)
		{
			cur->flag = 0;
			//go_heredoc()
		}
	}
	return (cur);
}

t_token	*read_pipe_redir(char **s, t_token *cur, t_str *buf)
{
	if (buf->len != 0)
		cur = push_token(T_WORD, buf, cur);
	push_str(buf, *((*s)++));
	if ((*(*(s)- 1) == '<' || *(*(s) - 1) == '>') && *(*(s) - 1) == **s)
	{
		push_str(buf, *((*s)++));
		cur = push_token(T_REDIRECT, buf, cur);
		if (*(*(s) - 1) == '<')
			cur->flag = 1;
	}
	else
	{
		if (*(*(s) - 1) == '|')
			cur = push_token(T_PIPE, buf, cur);
		else
			cur = push_token(T_REDIRECT, buf, cur);
	}
	return (cur);
}
