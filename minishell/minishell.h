/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 21:55:59 by gyopark           #+#    #+#             */
/*   Updated: 2023/01/28 18:44:51 by gyopark          ###   ########.fr       */
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

typedef struct str
{
	int		len;
	int		capacity;
	char	*s;
}	t_str;

typedef struct  s_token
{
	int		type;
	char	*str;
	struct s_token  *prev;
	struct s_token  *next;
}   t_token;

t_str	*make_str(void);
t_token	*make_token(void);
int		is_space(char c);
void 	push_str(t_str *str, char val);
void	resize_str(t_str *str);
t_token	*push_token(int type, t_str *str, t_token *prev);
void	clear_str(t_str *str);
void	resize_str(t_str *str);
void	free_str(t_str *str);
void	clear_str(t_str *str);
int		is_word_end(char s);
int		is_line_end(char s);
void	print_token(t_token *cur);
void	free_token(t_token *cur);
t_token	*read_pipe_redir(char **s, t_token *cur, t_str *buf);
t_token	*read_word(char **s, t_token *cur, t_str *buf, char **envp);
char	*conv_env(char *name);
int		is_env_char(char s);

#endif
