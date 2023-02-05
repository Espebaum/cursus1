/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 16:25:16 by gyopark           #+#    #+#             */
/*   Updated: 2023/02/04 22:42:29 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_env_num(char *envp)
{
	int		cnt;
	char	*temp;

	temp = envp;
	cnt = 0;
	while (*temp++ != '=')
		cnt++;
	if (cnt > 1)
		cnt--;
	return (cnt);
}

void	read_dquote_env(char **s, t_str *buf, char **envp, int *env_flag)
{
	t_str	*env;
	int		i;
	int		env_num;

	i = 0;
	env = make_str();
	while (!is_word_end(*(++(*s))) && **s != '\"')
	{
		if (**s == '$')
			break ;
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
	printf("buf->s %s\n", buf->s);
	(*env_flag)++;
	free_str(env);
}
//echo "$HOME$HOME$USER"
//strjoin