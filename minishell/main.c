/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 22:08:16 by gyopark           #+#    #+#             */
/*   Updated: 2023/01/29 17:57:18 by gyopark          ###   ########.fr       */
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
	int					*count;
	t_token				*head;
	struct termios		term;

	head = NULL;
	tcgetattr(STDIN_FILENO, &term);
	main_init(argc, argv);
	while (1)
	{
		count = (int *)malloc(sizeof(int) * 2);
		if (!count)
			return (0);
		count[0] = 0;
		count[1] = 0;
		line = readline("minishell \% ");
		if (!line)
			break ;
		if (*line != '\0')
			add_history(line);
		if (*line != '\0' && !is_str_space(line))
		{
			go_tokenize(line, envp, count, head);
			//printf("%d, %d\n", count[0], count[1]);
			//pipe_line(count, head, envp);
		}
		free_token(head);
		free(line);
		free(count);
		//system("leaks minishell | grep leaked"); //
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	return (0);
}
//main에서 head 포인터를 보관해야 함(free하기 위해서)