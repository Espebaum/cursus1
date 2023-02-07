/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in1.c                                        :+:      :+:    :+:   */
/*          	                                          +:+ +:+         +:+ */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 16:22:56 by youngski          #+#    #+#             */
/*   Updated: 2023/02/07 13:43:03 by youngski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_check(char *str)
{
	if (!ft_strncmp("echo", str, 4) && str[4] == 0)
	return 1;
	if (!ft_strncmp("cd", str, 2) && str[2] == 2)
	return 1;
	if (!ft_strncmp("pwd", str, 4) && str[4] == 0)
	return 1;
	if (!ft_strncmp("export", str, 7) && str[7] == 0)
	return 1;
	if (!ft_strncmp("unset", str, 6) && str[6] == 0)
	return 1;
	if (!ft_strncmp("env", str, 4) && str[4] == 0)
	return 1;
	if (!ft_strncmp("exit", str, 5) && str[5] == 0)
	return 1;
	return (0);
}

// t_token 의 구조체 안에 헤드를 가리키는 token *head를 추가해서
// 모든 토큰에서 헤드를 향해 갈 수 있도록 만들어주자
// 헤드 (str이 널인곳)에서만 envp원본을 가지고 있도록 만들어주고
// 여기서 수정하

// int	check_echo_option(char *str)
// {
// 	int	i;
// 	// - 로  시작  하는   것것
// }

char    **cutting_t(char **t, int *flag)
{
    int i;
    int j;
    char **temp;

    i = 0;
    (t)++;
    while (t[i])
    {
        temp = &t[i];
        j = 0;
        if (t[i][j] == '-')
        {
            j++;
            while (t[i][j] != 0)
            {
                if (t[i][j] != 'n' && t[i][j] != 0)
                    return (temp);
                j++;
            }
            if (t[i][j] == 0)
                *flag = 1;
        }
        else
            return (temp);
        i++;
    }
	if (i == 0)
		return (&t[i]);
    return (&t[--i]);
}

void	built_echo(char **t)
{
	int		flag;

	flag = 0;
	t = cutting_t(t, &flag);
	while (*t)
	{
		printf("%s", t[0]);
		if (flag == 0)
			printf("\n");
		else if (*(t + 1) != 0)
			printf(" ");
		t++;
	}
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
	if (!ft_strncmp("cd", str, 2) && str[2] == 2)
	{
		printf("check if word\n\n");
		built_cd(t);
	}
	if (!ft_strncmp("pwd", str, 4) && str[4] == 0)
		built_pwd();
	if (!ft_strncmp("export", str, 7) && str[7] == 0)
		built_export();
	if (!ft_strncmp("unset", str, 6) && str[6] == 0)
		built_unset();
	if (!ft_strncmp("env", str, 4) && str[4] == 0)
		built_env();
	if (!ft_strncmp("exit", str, 5) && str[5] == 0)
		exit(1);
	return (0);
}
