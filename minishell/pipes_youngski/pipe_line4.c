/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_line4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark < gyopark@student.42seoul.kr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 18:19:51 by youngski          #+#    #+#             */
/*   Updated: 2023/02/17 22:46:21 by youngski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**copy_orders(char **t, int i)
{
	char	**temp;
	char	**ret;

	temp = t;
	while (temp && temp[i])
		i++;
	if (i == 0)
	{
		ret = (char **)malloc(sizeof(char *) * 2);
		ret[1] = 0;
		free(t);
		t = ret;
		return (ret);
	}
	else
	{
		ret = (char **)malloc(sizeof(char *) * (i + 2));
		ret[i + 1] = 0;
		ret[i] = "";
	}
	i = -1;
	while (temp[++i])
		ret[i] = temp[i];
	free(t);
	return (ret);
}

char	**add_order(char **t, char *str, int flag)
{
	int		i;
	int		k;
	char	**temp;

	k = 0;
	i = 0;
	temp = t;
	while (temp[i])
		i++;
	i--;
	k = ft_strlen(str);
	if (flag != 0)
	{
		temp[i] = (char *)malloc(sizeof(char) * k + 1);
		ft_memcpy(temp[i], str, ft_strlen(str));
		temp[i][ft_strlen(str)] = 0;
	}
	else
	{
		temp[0] = (char *)malloc(sizeof(char) * k + 1);
		ft_memcpy(temp[0], str, ft_strlen(str));
		temp[0][ft_strlen(str)] = 0;
	}
	return (temp);
}
