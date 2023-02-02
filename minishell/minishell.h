/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 14:11:26 by gyopark           #+#    #+#             */
/*   Updated: 2023/02/02 22:13:59 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define SHE 10
# define DFL 11
# define IGN 12

# define T_ERROR	 6
# define T_REDIRECT  1
# define T_WORD      2
# define T_PIPE      3
# define T_SQUOTE    4
# define T_DQUOTE    5

# include <signal.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <termios.h>
# include <errno.h>
# include <string.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/wait.h>
# include "./libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

int	g_exit_code;

typedef struct s_str
{
	int		len;
	int		capacity;
	char	*s;
}	t_str;

typedef struct s_token
{
	int				type;
	int				cmds;
	char			*str;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

typedef struct s_data
{
	int		*pid;
	int		*doc_fd;
	char	**doc_name;
	int		doc_count;
	char	**envp;
	char	**path;
}	t_data;

t_token	*go_tokenize(char *cmd, char **envp, t_token *t);
void	set_signal(int sig_int, int sig_quit);

t_str	*make_str(void);
t_token	*make_token(void);
int		is_char_space(char c);
void	push_str(t_str *str, char val);
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
int		get_env_num(char *envp);

int		check_func(int *cnt);
int		is_valid_token(t_token *t);
int		check_syntax(t_token *head);
int		rule_error(int *type_arr, int len);
int		get_cmds_num(int *type_arr, int token_len);

int		open_pipe(t_token *head, char **envp, int cp_stdin);
char	**get_path(char **envp);
int		wait_all(pid_t last_pid);
int		exit_error(char *message, int signal, int exit_code);
t_token	*get_next_tmp(t_token *temp);
char	**get_path(char **envp);
void	execute(char **arg_cmd, char **envp);
char	*get_cmd(char **path, char *cmd);

// int		pipe_line(int *count, t_token *head, char **envp);
// int		init_fork(t_token **head, t_data *data, int i, int *heredoc_count);
// void	get_heredoc(t_token *head, t_data *data, int count);
// int		*find_heredoc_index(t_token *head, int count);
// char	**get_path(char **envp);
// char	*check_command(char **path, char *cmd);
// void	forked_child_work(t_data *data, t_token **head, int *pipes, int *hc);

// char	*get_limiter(t_token *head, int doc_index);
// void	heredoc_file_make(int doc_index, int doc_fd, char *limiter);
// void	close_all_opend_heredoc_fd(t_data *data, int count);
// int		free_pid_docs(int *pid, int *doc_fd);
// void	open_doc_file(t_data *data, char *t, int *i, int *k);

// int		output_redirection(int o_fd, t_token **head);
// int		input_redirection(int i_fd, t_token **head);
// int		append_redirection(int o_fd, t_token **head);
// int		heredoc_redirection(int i_fd, t_token **head, t_data *data, int *hc);
// void	dup_pipes(t_token **head, int *pipes, t_data *data);
// int		exit_error(char *message, int signal, int exit_code);
// int		wait_all(t_data data, pid_t last_pid);

// int		ft_perror(char *str, int exit_code);

#endif
