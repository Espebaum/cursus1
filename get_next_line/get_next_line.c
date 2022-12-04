/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 19:38:42 by gyopark           #+#    #+#             */
/*   Updated: 2022/12/04 22:40:00 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
		free(backup);
		return (NULL);
	}
	if (backup[i] == '\n')
		i++;
	str = ft_strdup(&backup[i]);
	if (!str)
		return (0);
	free(backup);
	return (str);
}

char	*make_line(char *backup, int j)
{
	char	*str;

	if (backup == NULL || backup[0] == '\0')
		return (NULL);
	while (backup[j] != '\n' && backup[j] != '\0')
		j++;
	if (backup[j] == '\n')
		str = malloc(sizeof(char) * (j + 2));
	else
		str = malloc(sizeof(char) * (j + 1));
	if (!str)
		return (NULL);
	j = 0;
	while (backup[j] != '\n' && backup[j] != '\0')
	{
		str[j] = backup[j];
		j++;
	}
	if (backup[j] == '\n')
		str[j++] = '\n';
	str[j] = '\0';
	return (str);
}

static ssize_t	buf_read(int fd, char *buf, char **backup)
{
	ssize_t	read_size;

	read_size = read(fd, buf, BUFFER_SIZE);
	if (read_size < 0)
	{
		free(buf);
		buf = 0;
		free(*backup);
		*backup = 0;
		return (-1);
	}
	buf[read_size] = '\0';
	return (read_size);
}

static char	*meet_eof(char **backup, char *buf)
{
	char	*line;

	free(buf);
	buf = 0;
	if (ft_strlen(*backup) == 0)
	{
		free(*backup);
		*backup = 0;
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
	int			j;

	j = 0;
	if (BUFFER_SIZE <= 0 || fd < 0 || fd >= OPEN_MAX)
		return (0);
	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (0);
	while (!ft_strchr(backup[fd], '\n'))
	{
		read_size = buf_read(fd, buf, &backup[fd]);
		if (read_size == -1)
			return (0);
		backup[fd] = ft_strjoin(backup[fd], buf);
		if (read_size == 0)
			return (meet_eof(&backup[fd], buf));
	}
	str = make_line(backup[fd], j);
	backup[fd] = cut_line(backup[fd]);
	free(buf);
	return (str);
}
