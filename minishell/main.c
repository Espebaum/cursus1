/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 22:08:16 by gyopark           #+#    #+#             */
/*   Updated: 2023/02/07 16:49:46 by gyopark          ###   ########.fr       */
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

void	main_init(int argc, __attribute__((unused)) char *argv[])
{
	struct termios		term;

	if (argc != 1)
		exit_error("argument input error", 0, 1);
	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	set_signal(SHE, SHE);
}

int	main(int argc, char **argv, char **envp)
{
	char				*line;
	t_cover				cover;
	t_doc				doc;
	struct termios		term;
	char				**builtin;

	builtin = (char **)malloc(sizeof(char *));
	builtin[0] = 0;
	cover.cp_stdin = dup(STDIN_FILENO);
	line = NULL;
	tcgetattr(STDIN_FILENO, &term);
	main_init(argc, argv);
	while (1)
	{
		init_fd(&(cover.data));
		line = init_line(line);
		if (*line != '\0' && !is_str_space(line))
		{
			if (doc_syntax(line) == -1)
			{
				syntax_err();
				continue ;
			}
			if (open_heredoc(&doc, line) == -1)
				continue ;
			cover.head = go_tokenize(line, envp, cover.head);
			if (check_syntax(cover.head) == -1)
			{
				syntax_err();
				continue ;
			}
			init_data(&(cover.data), doc, envp, cover.head);
			if (cover.head->cmds == 1)
			{
				builtin = read_cmd(&(cover.data), &(cover.head), 0, NULL); //head를 순회하면서 t를 만든다.
				if (check_builtin(builtin)) //builtin[0] == ft_strnstr(builtin)
					continue ;
			}
			g_exit_code = pipe_line(cover.data, cover.head, cover);
			free_token(cover.head);
			set_signal(SHE, SHE);
		}
		free(line);
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	return (g_exit_code);
}
