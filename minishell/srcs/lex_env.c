/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 16:25:16 by gyopark           #+#    #+#             */
/*   Updated: 2023/01/28 21:13:11 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/** char	g_env[100] = "home"; */
// 전역변수 구조체 링크드리스트로 관리하는 환경변수 목록에서 확인해야함.

/** char	*conv_env(char *name) */
/** { */
/**     (void) name; */
/**     return (g_env); */
/** } */

/** int	is_env_char(char s) */
/** { */
/**     if (('0' <= s && s <= '9') || ('a' <= s && s <= 'z') */
/**         || ('A' <= s && s <= 'Z') || s == '_') */
/**         return (1); */
/**     return (0); */
/** } */

int	get_env_num(char *envp)
{
	int		cnt;
	char	*temp;

	temp = envp;
	cnt = 0;
	while (*temp++ != '=')
		cnt++;
	cnt--;
	return (cnt);
}
