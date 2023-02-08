/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 22:08:16 by gyopark           #+#    #+#             */
/*   Updated: 2023/02/08 22:05:11 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*init_line(char *line)
{
	line = readline("YOUNGSHELL $ ");
	if (!line)
	{
		printf("exit\n");
		exit(0);
	}
	if (*line != '\0')
		add_history(line);
	return (line);
}

int	is_str_space(char *line)
{
	while (*line)
	{
		if (*line != 32 && !(*line >= 9 && *line <= 13))
		{
			return (0);
		}
		line++;
	}
	return (1);
}

void	init_prompt_sig(int argc, __attribute__((unused)) char *argv[])
{
	struct termios		term;

	if (argc != 1)
		exit_error("argument input error", 0, 1);
	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	set_signal(SHE, SHE);
}

t_cover	*init_cover(t_cover *cover)
{
	cover->data = (t_data *) malloc(sizeof(t_data));
	cover->head = (t_token *) malloc(sizeof(t_token));
	cover->doc = (t_doc *) malloc(sizeof(t_doc));
	cover->cp_stdin = dup(STDIN_FILENO);
	cover->builtin = (char **)malloc(sizeof(char *));
	cover->builtin[0] = 0;
	return (cover);
}

int	doc_check(t_cover *cover, char *line, int *check)
{
	if (doc_syntax(line) == -1)
	{
		*check = 1;
		return (syntax_err());
	}
	if (open_heredoc(cover->doc, line) == -1)
	{
		*check = 1;
		return (syntax_err());
	}
	return (0);
}

int	do_builtin(t_cover *cover)
{
	cover->temp = cover->head;
	cover->builtin = read_cmd(cover->data, &(cover->temp), \
	&(cover->doc->zero));
	if (check_builtin(cover->builtin) >= 0)
		return (-1);
	return (0);
}

int	handle_line(char *line, t_cover *cover, char **envp)
{
	int	check;

	check = 0;
	if (doc_check(cover, line, &check) == -1)
		return (-1);
	cover->head = go_tokenize(line, envp, cover->head);
	if (check_syntax(cover->head, check) == -1)
		return (-1);
	init_data(cover->data, *(cover->doc), envp, cover->head);
	if (cover->head->cmds == 1)
		if (do_builtin(cover) == -1)
			return (-1);
	g_exit_code = pipe_line(*(cover->data), cover->head, *cover);
	free_token(cover->head);
	set_signal(SHE, SHE);
	return (g_exit_code);
}

int	main(int argc, char **argv, char **envp)
{
	char				*line;
	t_cover				*cover;
	struct termios		term;

	cover = (t_cover *)malloc(sizeof(t_cover));
	cover = init_cover(cover);
	line = NULL;
	tcgetattr(STDIN_FILENO, &term);
	init_prompt_sig(argc, argv);
	while (1)
	{
		init_fd(cover->data);
		line = init_line(line);
		if (*line != '\0' && !is_str_space(line))
			if (handle_line(line, cover, envp) == -1)
				continue ;
		free(line);
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	return (g_exit_code);
}
// (1) 부모 echo 실행시 출력 리다이렉션으로 안바뀌고 표준출력된
// (2) ech"o hio" 세그폴트
