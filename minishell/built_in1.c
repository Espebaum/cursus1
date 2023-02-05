/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in1.c                                        :+:      :+:    :+:   */
/*          	                                          +:+ +:+         +:+ */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 16:22:56 by youngski          #+#    #+#             */
/*   Updated: 2023/02/05 17:08:08 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_check(char *str)
{
	return (ft_strncmp("cd", str, ft_strlen("cd")) == 0 || \
	ft_strncmp("echo", str, ft_strlen("echo")) == 0 || \
	ft_strncmp("pwd", str, ft_strlen("pwd")) == 0 || \
	ft_strncmp("export", str, ft_strlen("export")) == 0 || \
	ft_strncmp("unset", str, ft_strlen("unset")) == 0 || \
	ft_strncmp("env", str, ft_strlen("env")) == 0 || \
	ft_strncmp("exit", str, ft_strlen("exit")));
}

// t_token 의 구조체 안에 헤드를 가리키는 token *head를 추가해서
// 모든 토큰에서 헤드를 향해 갈 수 있도록 만들어주자
// 헤드 (str이 널인곳)에서만 envp원본을 가지고 있도록 만들어주고
// 여기서 수정하
void	built_echo(char **t)
{
	int		i;
	int		flag;

	i = 1;
	flag = 0;
	t = 0;
	while (t[i])
	{
		if (!ft_strncmp(t[1], "-n", 2))
		{
			flag = 1;
			i++;
			continue ;
		}
		if (!ft_strncmp(t[1], "$?", 2))
		{
			printf("%d", g_exit_code);
			printf("%s", &t[1][0] + 2);
			i++;
		}
		if (flag == 1)
			printf("%s", t[i]);
		else
			printf("%s\n", t[i]);
		i++;
	}
	printf("working\n");
	exit(1);
}

void	built_cd(char **t)
{
	printf("cd : working : %s\n", t[1]);
	chdir(t[1]);
	exit(1);
}

void	built_pwd()
{
	char	t[2048];

	getcwd(t, 2048);
	printf("%s\n", t);
	free(t);
	exit(1);
}

void	built_export()
{
	exit(1);
}

void	built_unset()
{
	exit(1);
}

void	built_env()
{
	exit(1);
}

int	check_builtin(char **t, t_data data, char *str)
{
	(void)data;

	if (!ft_strncmp("echo", str, 4) && str[4] == 0)
		built_echo(t);
	if (!ft_strncmp("cd", str, 2))
	{
		printf("check if word\n\n");
		built_cd(t);
	}
	if (!ft_strncmp("pwd", str, 4))
		built_pwd();
	if (!ft_strncmp("export", str, 7))
		built_export();
	if (!ft_strncmp("unset", str, 6))
		built_unset();
	if (!ft_strncmp("env", str, 4))
		built_env();
	if (!ft_strncmp("exit", str, 5))
		exit(1);
	return (0);
}
