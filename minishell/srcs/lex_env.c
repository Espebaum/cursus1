/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 16:25:16 by gyopark           #+#    #+#             */
/*   Updated: 2023/02/04 17:52:10 by gyopark          ###   ########.fr       */
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
