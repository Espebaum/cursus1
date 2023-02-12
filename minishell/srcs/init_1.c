/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark < gyopark@student.42seoul.kr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 13:48:47 by gyopark           #+#    #+#             */
/*   Updated: 2023/02/12 18:29:20 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void	init_fd(t_data *data)
{
	data->i_flag = 0;
	data->o_flag = 0;
	data->io_fd[0] = dup(0);
	data->io_fd[1] = dup(1);
}

int	init_data(t_data *data, t_doc doc, char **envp, t_token *head)
{
	data->path = get_path(envp);
	data->envp = envp;
	data->pid = (int *)malloc(sizeof(int) * head->cmds);
	if (!(data->pid))
		return (1);
	data->doc_name = doc.name;
	return (0);
}
