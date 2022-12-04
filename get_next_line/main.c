/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 19:13:22 by gyopark           #+#    #+#             */
/*   Updated: 2022/12/04 16:16:26 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <limits.h>

int	main(void)
{
	char	*line;
	int		fd;
	int		i;

	printf("%d\n", OPEN_MAX);
	i = 1;
	fd = open("test1.txt", O_RDONLY);
	if (!fd)
	{
		printf("\nError in open");
		return (0);
	}
	while (fd)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		printf("Gnl %d line : %s", i++, line);
	}
	printf("\n");
	free(line);
	close(fd);
	return (0);
}
