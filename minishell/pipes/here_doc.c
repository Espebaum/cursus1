/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngski <youngski@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 16:03:57 by youngski          #+#    #+#             */
/*   Updated: 2023/01/29 17:47:29 by youngski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe_line.h"

void	run_heredoc(int count, t_token *head)
{
	int		i;
	char	*t;

	t = ".heredoc"
	i = 0;
	while (i < count)
	{
		if (access(	)== 0)
		head->doc_fd[i] = open((char *)i, O_WRONLY);
	}
}

int	cmp_heredoc(t_token head)
{
	if (head->type != 0)
		return (0);
	if (!ft_memcmp(head->str, "<<"))
	{
		//다르다면?
		return (0);
	}	
	return (1);

}

int	check_heredoc(t_token head)
{
	int	flag;
	
	flag = 0;
	while (head || head->type != 1) //type로 보아 파이프가 아니면 동작
	{
		if (cmp_heredoc(head))
		{
			flag = 1;
			break;
		}
		head = head->next;
	}
	if (flag == 1)
		return (1);
	else
		return (0)
}
