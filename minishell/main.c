/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark < gyopark@student.42seoul.kr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 22:08:16 by gyopark           #+#    #+#             */
/*   Updated: 2023/02/18 16:03:40 by gyopark          ###   ########.fr       */
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

int	do_builtin(t_cover *cover, t_list *head, char **envp)
{
	int		ret;

	ret = 0;
	cover->temp = cover->head;
	cover->builtin = read_cmd(cover->data, &(cover->temp), \
	&(cover->doc->zero));
	dup_pipes(NULL, cover->data->io_fd, cover->data);
	if (check_builtin(cover->builtin, head, envp) >= 0)
		ret = -1;
	free_spl(cover->builtin); // <- leaks fixed
	dup2(cover->data->io_fd[1], 1);
	close(cover->data->io_fd[1]);
	return (ret);
}

int	doc_check(t_cover *cover, char *line)
{
	int	doc;

	doc = doc_syntax(line);
	if (doc == -1)
		return (syntax_err());
	if (doc == 1)
	{
		doc = open_heredoc(cover->doc, line);
		if (doc == -1)
			return (-1);
		return (doc);
	}
	return (doc);
}
//리턴값 -1 : syntax 오류
//doc -> 0 히어독 아님
//doc -> 1 히어독인데 정상 종료
//doc -> 2 히어독인데 Ctrl C
//doc -> 3 히어독인데 Ctrl D

int	is_head_null(t_cover *cover)
{
	t_token	*temp;

	temp = cover->head->next;
	if (temp == NULL)
	{
		free_token(cover->head);
		g_exit_code = 0;
		return (1);
	}
	return (0);
}

int	is_path_gone(char **path)
{
	if (path && path[0] != NULL)
		return (1);
	return (0);
}

int	handle_line(char *line, t_cover *cover, char **envp, t_list *head)
{
	int		doc;

	doc = doc_check(cover, line);
	if (doc == -1)
		return (-1);
	else if (doc == 2)
		return (-1);
	else if (doc == 3)
		return (-1);
	cover->head = go_tokenize(line, envp, cover->head);
	if (is_head_null(cover) == 1)
		return (g_exit_code);
	if (check_syntax(cover->head) == -1)
		return (-1);
	init_data(cover->data, *(cover->doc), envp, cover->head);
	if (cover->head->cmds == 1)
		if (do_builtin(cover, head, envp) == -1)
			return (-1);
	g_exit_code = pipe_line(*(cover->data), cover->head, *cover, head);
	free_token(cover->head);
	set_signal(SHE, SHE);
	return (g_exit_code);
}
//heredoc인데 오류 -> 반환값 g_exit_code 1;
//heredoc인데 정상종료 -> g_exit_code 건들지 않음
//heredoc아님 ->

void	leak_check(void)
{
	system("leaks a.out");
}

int	main(int argc, char **argv, char **envp)
{
	char				*line;
	t_cover				*cover;
	struct termios		term;
	t_list				*head;

	atexit(leak_check);
	line = NULL;
	cover = NULL;
	init_env_list(envp, &head);
	envp = make_envp_arr(head, 0);
	cover = init_cover(cover);
	tcgetattr(STDIN_FILENO, &term);
	init_prompt_sig(argc, argv);
	init_fd(cover->data);
	while (1)
	{
		line = init_line(line);
		if (*line != '\0' && !is_str_space(line))
			handle_line(line, cover, envp, head);
		free_spl(envp);
		envp = make_envp_arr(head, 0);
		free(line);
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	return (g_exit_code);
}
