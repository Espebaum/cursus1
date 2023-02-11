/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark < gyopark@student.42seoul.kr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 22:08:16 by gyopark           #+#    #+#             */
/*   Updated: 2023/02/11 22:09:30 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_str_space(char *line)
{
	while (*line)
	{
		if (*line != 32 && !(*line >= 9 && *line <= 13))
			return (0);
		line++;
	}
	return (1);
}

int	doc_check(t_cover *cover, char *line)
{
	if (doc_syntax(line) == -1)
		return (syntax_err());
	if (open_heredoc(cover->doc, line) == -1)
		return (-1);
	return (0);
}

int	do_builtin(t_cover *cover, t_list *head)
{
	cover->temp = cover->head;
	cover->builtin = read_cmd(cover->data, &(cover->temp), \
	&(cover->doc->zero));
	if (check_builtin(cover->builtin, head) >= 0)
		return (-1);
	return (0);
}

int	handle_line(char *line, t_cover *cover, char **envp, t_list *head)
{
	if (doc_check(cover, line) == -1)
		return (-1);
	cover->head = go_tokenize(line, envp, cover->head);
	if (check_syntax(cover->head) == -1)
		return (-1);
	init_data(cover->data, *(cover->doc), envp, cover->head);
	if (cover->head->cmds == 1)
		if (do_builtin(cover, head) == -1)
			return (-1);
	g_exit_code = pipe_line(*(cover->data), cover->head, *cover, head);
	free_token(cover->head);
	set_signal(SHE, SHE);
	return (g_exit_code);
}

int	main(int argc, char **argv, char **envp)
{
	char				*line;
	t_cover				*cover;
	struct termios		term;
	t_list				*head;

	init_env_list(envp, &head);
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
			if (handle_line(line, cover, envp, head) == -1)
				continue ;
		free(line);
		envp = make_envp_arr(head);
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	return (g_exit_code);
}
// (1) 부모 echo 실행시 출력 리다이렉션으로 안바뀌고 표준출력된
// (2) ech"o hio" 세그폴트
