/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_line.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngski <youngski@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 15:44:58 by youngski          #+#    #+#             */
/*   Updated: 2023/01/29 16:41:21 by youngski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPE_LINE_H
# define PIPE_LINE_H

#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>

typedef struct	s_data
{
	int		*pid;
	int		*doc_fd;
	char	*doc_name;
	int		doc_count;
}				t_data;

#endif
