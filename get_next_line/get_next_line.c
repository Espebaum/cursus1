/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 19:38:42 by gyopark           #+#    #+#             */
/*   Updated: 2022/12/05 21:44:57 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	str_free(char **str)
{
	free(*str);
	*str = NULL;
}

char	*cut_line(char *backup)
{
	int		i;
	char	*str;

	i = 0;
	if (backup == NULL)
		return (NULL);
	while (backup[i] != '\n' && backup[i] != '\0')
		i++;
	if (backup[i] == '\0')
	{
		str_free(&backup);
		return (NULL);
	}
	if (backup[i] == '\n')
		i++;
	str = ft_strdup(&backup[i]);
	if (!str)
	{
		str_free(&backup);
		return (NULL);
	}
	str_free(&backup);
	return (str);
}

char	*make_line(char *backup, int i)
{
	char	*str;

	if (backup == NULL || backup[0] == '\0')
		return (NULL);
	while (backup[i] != '\n' && backup[i] != '\0')
		i++;
	if (backup[i] == '\n')
		str = malloc(sizeof(char) * (i + 2));
	else
		str = malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (backup[i] != '\n' && backup[i] != '\0')
	{
		str[i] = backup[i];
		i++;
	}
	if (backup[i] == '\n')
		str[i++] = '\n';
	str[i] = '\0';
	return (str);
}

static char	*meet_eof(char **backup, char *buf, int read_size)
{
	char	*line;

	if (read_size == -1)
	{
		str_free(&buf);
		str_free(backup);
		return;
	}
	str_free(&buf);
	if (ft_strlen(*backup) == 0)
	{
		str_free(backup);
		return (0);
	}
	else
	{
		line = *backup;
		*backup = 0;
		return (line);
	}
}

char	*get_next_line(int fd)
{
	char		*buf;
	static char	*backup[OPEN_MAX];
	char		*str;
	int			read_size;

	if (BUFFER_SIZE <= 0 || fd < 0 || fd >= OPEN_MAX)
		return (0);
	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (0);
	while (!ft_strchr(backup[fd], '\n'))
	{
		read_size = read(fd, buf, BUFFER_SIZE);
		if (read_size <= 0)
			return (meet_eof(&backup[fd], buf, read_size));
		buf[read_size] = '\0';
		backup[fd] = ft_strjoin(backup[fd], buf);
	}
	str = make_line(backup[fd], 0);
	backup[fd] = cut_line(backup[fd]);
	str_free(&buf);
	if (!str || !backup[fd])
		return (NULL);
	return (str);
}
