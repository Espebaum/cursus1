/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 22:08:16 by gyopark           #+#    #+#             */
/*   Updated: 2023/02/02 22:44:25 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exit_error(char *message, int signal, int exit_code)
{
	char	*error_str;

	error_str = strerror(errno);
	write(2, message, ft_strlen(message));
	write(2, error_str, ft_strlen(error_str));
	exit (exit_code + signal);
	return (1);
}

char	*init_line(char *line)
{
	line = readline("minishell $ ");
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
	t_token				*head;
	struct termios		term;
	int					cp_stdin;

	cp_stdin = dup(STDIN_FILENO);
	line = NULL;
	head = NULL;
	tcgetattr(STDIN_FILENO, &term);
	main_init(argc, argv);
	while (1)
	{
		line = init_line(line);
		if (*line != '\0' && !is_str_space(line))
		{
			//히어독 인파일 열기;
			head = go_tokenize(line, envp, head);
			if (check_syntax(head) == -1)
				continue ;
			g_exit_code = open_pipe(head, envp, cp_stdin);
			free_token(head);
		}
		free(line);
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	return (g_exit_code);
}
//main에서 head 포인터를 보관해야 함(free하기 위해서)
