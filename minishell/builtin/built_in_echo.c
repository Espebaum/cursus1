/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark < gyopark@student.42seoul.kr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 20:29:43 by gyopark           #+#    #+#             */
/*   Updated: 2023/02/14 20:30:08 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	cutting_t2(char **t, int *flag, int i, int *j)
{
	(*j)++;
	while (t[i][*j] != 0)
	{
		if (t[i][*j] != 'n' && t[i][*j] != 0)
			return (1);
		(*j)++;
	}
	if (t[i][(*j) - 1] == '-')
		return (1);
	if (t[i][*j] == 0)
		*flag = 1;
	return (0);
}

char	**cutting_t(char **t, int *flag)
{
	int		i;
	int		j;
	char	**temp;

	i = 0;
	(t)++;
	while (t[i])
	{
		temp = &t[i];
		j = 0;
		if (t[i][j] == '-')
		{
			if (cutting_t2(t, flag, i, &j))
				return (temp);
		}
		else
			return (temp);
		i++;
	}
	if (i == 0)
		return (temp);
	return (&t[i]);
}

int	built_echo(char **t)
{
	int	flag;

	flag = 0;
	if (!ft_strncmp(t[0], "echo", 5) && t[1] == NULL)
	{
		printf("\n");
		return (1);
	}
	t = cutting_t(t, &flag);
	while (t && t[0])
	{
		if (t && t[0] != NULL)
		{
			printf("%s", t[0]);
			if (*(t + 1) != 0)
				printf(" ");
		}
		else
			printf("\n");
		t++;
	}
	if (flag == 0)
		printf("\n");
	g_exit_code = 0;
	return (1);
}
