/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 16:22:56 by youngski          #+#    #+#             */
/*   Updated: 2023/02/04 17:02:51 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int builtin_check(char *str)
{
    if (!ft_strncmp("echo", str, 5))
        return 0;
    if (!ft_strncmp("cd", str, 3))
        return 0;
    if (!ft_strncmp("pwd", str, 4))
        return 0;
    if (!ft_strncmp("export", str, 7))
        return 0;
    if (!ft_strncmp("unset", str, 6))
        return 0;
    if (!ft_strncmp("env", str, 4))
        return 0;
    if (!ft_strncmp("exit", str, 6))
        return 0;
    return 1;
}

