/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 21:55:59 by gyopark           #+#    #+#             */
/*   Updated: 2023/01/26 16:37:08 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#define T_ERROR		6
#define T_REDIRECT  0
#define T_WORD      1
#define T_PIPE      2
#define T_SQUOTE    3
#define T_DQUOTE    4

#include <signal.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <stdlib.h>
#include <termios.h>
#include "./libft/libft.h"
#include <string.h>

#endif
