/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngski <youngski@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 16:19:44 by youngski          #+#    #+#             */
/*   Updated: 2023/02/21 16:32:14 by youngski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_made_builtin(char **builtin)
{
    int result;

    result = 1;
    if ((!ft_strncmp(builtin[0], "/bin/echo", ft_strlen("/bin/echo")) && access(builtin[0], X_OK) != -1))
        result = 0;
	else if ((!ft_strncmp(builtin[0], "/usr/bin/cd", ft_strlen("/usr/bin/cd")) && access(builtin[0], X_OK) != -1))
        result = 0;
	else if ((!ft_strncmp(builtin[0], "/bin/pwd", ft_strlen("/bin/pwd")) && access(builtin[0], X_OK) != -1))
        result = 0;
	else if ((!ft_strncmp(builtin[0], "/usr/bin/env", ft_strlen("/usr/bin/env")) && access(builtin[0], X_OK) != -1))
        result = 0;
    return (result);
}
//unset export exit = no way
