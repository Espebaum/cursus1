/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark < gyopark@student.42seoul.kr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 14:11:26 by gyopark           #+#    #+#             */
/*   Updated: 2023/02/13 19:12:49 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define SHE 10
# define DFL 11
# define IGN 12
# define DOC 13

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
//# include <string.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include "./libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include "./get_next_line/get_next_line.h"

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
	int				flag;
}	t_token;

typedef struct s_doc
{
	char	**name;
	int		count;
	char	**limiters;
	int		zero;
}	t_doc;

typedef struct s_data
{
	int		*pid;
	int		i_flag;
	int		o_flag;
	char	**doc_name;
	char	**envp;
	char	**path;
	int		io_fd[2];
}	t_data;

typedef struct s_cover
{
	t_data	*data;
	t_doc	*doc;
	t_token	*head;
	t_token	*temp;
	int		cp_stdin;
	char	**builtin;
}	t_cover;

typedef struct s_list
{
	char			*key;
	char			*value;
	struct s_list	*next;
}	t_list;

typedef struct s_tuple
{
	t_token	**head;
	t_data	*data;
}	t_tuple;

t_token	*go_tokenize(char *cmd, char **envp, t_token *t);
void	set_signal(int sig_int, int sig_quit);
int		doc_syntax(char *str);

//

//init functions
t_cover	*init_cover(t_cover *cover);
void	init_prompt_sig(int argc, __attribute__((unused)) char *argv[]);
char	*init_line(char *line);
void	init_fd(t_data *data);
int		init_data(t_data *data, t_doc doc, char **envp, t_token *head);
t_doc	*init_doc(t_doc *doc);

//heredoc functions
int		get_doc_count(char **doc_str);
void	make_inside_char_double(int *i, int *count, char *line_temp, char *ret);
void	make_inside_char_single(int *i, int *count, char *line_temp, char *ret);
void	make_pure_word(int *i, int *count, char *line_temp, char *ret);
char	**myfunc_split(char *line, int i, int j, int count);
void	count_inside_char(int *i, int *count, char *line_temp, char my_char);
void	count_pure_word(int *i, int *count, char *line_temp);
int		count_space(char *line);
void	make_pure_word(int *i, int *count, char *line_temp, char *ret);
char	**myfunc_split(char *line, int i, int j, int count);
void	init_split(int *i, int *j, char *line, char **line_temp);
int		skip_space(int *i, char **line_temp);
char	**call_next(char *line_temp, char **ret, char *line, int i);
void	part_make_line(int *i, int *j, int *count, char **line_temp);
int		doc_parent(int idx, int count, t_doc **doc, int *pipe_fd);
void	doc_child(int idx, int count, t_doc **doc, int *pipe_fd);
void	make_doc_files(int count, t_doc *doc);
int		open_file(char *filename, int idx, t_doc **doc, int *pipe_fd);

//tokenize functions
t_str	*make_str(void);
t_token	*make_token(void);
char	**deep_copy_env(char **envp);
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
int		read_env(char **s, t_str *buf, char **envp);
int		is_env_char(char s);
int		get_env_num(char *envp);
int		check_all_dollar(t_str **buf, char **str);
int		env_read(t_str **buf, t_str **env, char *g_str);
int		make_env_buf(t_str **buf, t_str **env, char **envp, char *meta_str);
char	*check_meta_chr(t_str **env);
int		is_meta_chr(char c);

//execute function
char	**keep_execve_par(t_token **head, char **builtin, int *cmd_flag);
char	**keep_execve_chd(t_data data, t_token **head, char **t, int *cmd_flag);
int		check_func(int *cnt);
int		check_syntax(t_token *head);
int		rule_error(int *type_arr, int len);
int		get_cmds_num(int *type_arr, int token_len);
int		syntax_err(void);
int		builtin_check(char *str);

int		exit_error(char *message, int signal, int exit_code);
int		ft_perror(char *str, int signal, int exit_code);

int		open_heredoc(t_doc *doc, char *line);
int		pipe_line(t_data data, t_token *head, t_cover cover, t_list *env_head);

int		init_fork(t_tuple tup, int i, int *heredoc_count, t_list *env_head);
void	get_heredoc(t_token *head, t_data *data, int count);
int		*find_heredoc_index(t_token *head, int count);
char	**get_path(char **envp);
int		check_command(char **path, char *cmd);
void	forked_child_work(t_tuple tup, int *pipes, int *hc, t_list *env_head);
char	**copy_orders(char **t);
char	**add_order(char **t, char *str, int flag);

char	**get_limiter(char **doc_str, t_doc *doc);
void	heredoc_file_make(int fd, char *limiter, int *pipe_fd);
void	close_all_opend_heredoc_fd(t_data *data, int count);
int		free_pid_docs(int *pid, int *doc_fd);
void	open_doc_file(t_data *data, char *t, int *i, int *k);
void	read_dquote_env(char **s, t_str *buf, char **envp);

int		output_redirection(int o_fd, t_token **head, \
							t_data *data, int cmd_flag);
int		input_redirection(int i_fd, t_token **head, t_data *data, int cmd_flag);
int		append_redirection(int o_fd, t_token **head, \
							t_data *data, int cmd_flag);
int		heredoc_redirection(t_token **head, t_data *data, \
		int *heredoc_count, int cmd_flag);
void	dup_pipes(t_token **head, int *pipes, t_data *data);
int		exit_error(char *message, int signal, int exit_code);
int		wait_all(pid_t last_pid);
int		check_builtin(char **t, t_list *head, char **envp);
char	**read_cmd(t_data *data, t_token **head, int *heredoc_count);
char	**keep_execve(t_data data, t_token **head, char **t, int *flag);
void	init_fd(t_data *data);
int		ft_max(int a, int b);

//env and export func
t_list	*init_env_list(char **env, t_list **head);
char	**make_envp_arr(t_list *head);
void	print_env(t_list *head);
void	print_export(t_list *head);
void	new_value(t_list **head, char *key, char *value);
int		env_error_check(char *key);

#endif
