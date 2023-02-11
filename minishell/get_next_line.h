/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngski <youngski@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 20:31:18 by youngski          #+#    #+#             */
/*   Updated: 2022/11/30 20:31:23 by youngski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_mynode
{
	char				*content;
	int					fd;
	struct s_mynode		*next;
	ssize_t				size;
}						t_mynode;

char		*get_next_line(int fd);
char		*appending_save(char *dest, t_mynode *temp_n);
char		*make_return(t_mynode *temp, t_mynode **root);
char		*get_next_line(int fd);
char		*free_node(t_mynode **root, int fd);
int			read_line(t_mynode *temp, t_mynode **root);
t_mynode	*create_node(int fd);
t_mynode	*find_node(t_mynode **root, int fd);

#endif
