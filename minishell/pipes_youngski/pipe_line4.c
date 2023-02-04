/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_line4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 18:19:51 by youngski          #+#    #+#             */
/*   Updated: 2023/02/04 20:10:33 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**copy_orders(char **t)
{
	int		i;
	int		k;
	char	**temp;
	char	**ret;

	i = 0;
	k = 0;
	temp = t;
	while (temp && temp[i])
	{
		i++;
	}
	if (i == 0)
	{
		ret = (char **)malloc(sizeof(char *) * 2);
		ret[1] = 0;
		t = ret;
		return (ret);
	}
	else
	{
		ret = (char **)malloc(sizeof(char *) * (i + 2));
		ret[i + 1] = 0;
	}
	i = 0;
	while (temp[i])
	{
		ret[i] = temp[i];
		i++;
	}
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
	while (temp[i]){
		printf("my i = %d\n",i);
		i++;
	}
	i--;
	k = ft_strlen(str);
	printf("before : str : %s\n\n", str);
	if (flag != 0)
	{
		temp[i] = (char *)malloc(sizeof(char) * k + 1);
		k = 0;
		ft_memcpy(temp[i], str, ft_strlen(str));
		temp[i][ft_strlen(str)] = 0;
		printf("copy i :%d , str : %s\n\n",i, temp[i]);

		return (temp);
	}
	else
	{
		temp[0] = (char *)malloc(sizeof(char) * k + 1);
		k = 0;
		ft_memcpy(temp[0], str, ft_strlen(str));
		temp[0][ft_strlen(str)] = 0;
		printf("copy i :%d , str : %s\n\n",i, temp[i]);

		return (temp);
	}
}
