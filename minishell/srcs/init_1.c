/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark < gyopark@student.42seoul.kr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 13:48:47 by gyopark           #+#    #+#             */
/*   Updated: 2023/02/18 18:27:35 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cover	*init_cover(t_cover *cover)
{
	cover = (t_cover *)malloc(sizeof(t_cover));
	cover->head = NULL;
	cover->data = (t_data *) malloc(sizeof(t_data));
	cover->data->doc_name = NULL;
	cover->data->path = NULL;
	cover->doc = (t_doc *) malloc(sizeof(t_doc));
	cover->doc->limiters = NULL;
	cover->cp_stdin = dup(STDIN_FILENO);
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
	char	**temp;

	temp = deep_copy_env(envp);
	if (is_path_gone(data->path) == 1)
		free_spl(data->path);
	data->path = NULL;
	data->path = get_path(temp);
	data->envp = envp;
	if (head->cmds != 0)
		data->pid = (int *)malloc(sizeof(int) * head->cmds);
	else
		data->pid = NULL;
	if (!(data->pid))
		return (1);
	if (data->doc_name)
		free_spl(data->doc_name);
	data->doc_name = NULL;
	data->doc_name = doc.name;
	free_spl(temp);
	return (0);
}
