#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>

char	*get_next_line(int fd)
{
	char	backup[100000];
	char	buf;
	char	*str;
	int		i;
	int		read_size;

	i = 0;
	backup[0] = 0;
	while (1)
	{
		read_size = read(fd, &buf, 1);
		if (read_size < 0 || (read_size == 0 && backup[0] == '\0'))
			return (0);
		if (read_size == 0)
			break ;
		backup[i] = buf;
		i++;
		if (buf == '\n')
			break ;
	}
	backup[i] = '\0';
	str = (char *)malloc(sizeof(char) * (i + 1));
	while (i >= 0)
	{
		str[i] = backup[i];
		i--;
	}
	return (str);

}

/** int	main(void) */
/** { */
/**     char	*line; */
/**     int		fd; */
/**     int		i; */
/**  */
/**     i = 1; */
/**     fd = open("test.txt", O_RDONLY); */
/**     while (fd) */
/**     { */
/**         line = get_next_line(fd); */
/**         if (!line) */
/**             break ; */
/**         printf("Gnl %d line : %s", i++, line); */
/**         free(line); */
/**     } */
/**     free(line); */
/**     close(fd); */
/**     return (0); */
/** } */
