/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 19:13:22 by gyopark           #+#    #+#             */
/*   Updated: 2022/12/16 22:38:10 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <limits.h>
#include <sys/fcntl.h>

int	main(void)
{
	char	*line;
	int		fd;
	int		i;

	i = 1;
	fd = open("test.txt", O_RDONLY);
	printf("fd : %d\n", fd);
	while (fd)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		printf("Gnl %d line : %s", i++, line);
		free(line);
	}
	free(line);
	close(fd);
	return (0);
}
