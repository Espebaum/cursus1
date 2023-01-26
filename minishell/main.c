/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 22:08:16 by gyopark           #+#    #+#             */
/*   Updated: 2023/01/26 12:45:54 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_whitespace(char *line)
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

void	main_init(int argc, char *argv[])
{
	struct termios	term;

	if (argc != 1)
		exit_with_err("argument input error", NULL, 126);
	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	set_signal(SHE, SHE); // 시그널은 후술
	g_exit_code = 0;
	(void)argc;
	(void)argv;
}
int	main(int argc, char *argv[], char *envp[])
{
	char				*line;
	t_cmd				*cmd;
	t_env				env_head;
	struct termios		term;

	tcgetattr(STDIN_FILENO, &term);
	main_init(argc, argv);
	while (1)
	{
		line = readline("minishell $ ");
		if (!line)
			break ;
		if (*line != '\0')
			add_history(line);
		if (*line != '\0' && !is_whitespace(line))
		{
			// 실제 동작이 들어가는 지점
		}
		free(line);
		//system("leaks minishell | grep leaked"); //
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}
